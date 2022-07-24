#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

//int arraySort[pair_count];
int placement = 0;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int a, int b);
bool is_in_the_array(int liste_de_j[], int a); 
//bool beubeu_check(int pairs[].winner, int pairs[].loser, int inside)

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
        int j = 0;
       for (int i = 0; i < candidate_count; i++)
       {

                 if (strcmp(name, candidates[i]) == 0 )
                 {
                        ranks[rank] = i;
                       // printf("%i %i\n", rank, i);
                        return true;
                }
       }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int j = 0; j < candidate_count; j++)
    {
        for(int q = 0; q < candidate_count; q++)
        {
            if (j < q)
            {
                preferences[ranks[j]][ranks[q]]++;
            }
        }
    }
    //ici on a un grille qui permet de voir quelles paires ont gagné face à d'autres
    //le truc c'est qu'on a la paire et le nombre de fois qu'elles ont gagné
    printf("\n");

   // for (int i = 0; i < candidate_count; i++) {
   //     for (int j = 0; j < candidate_count; j++) {
   //         printf("%i ", preferences[i][j]);
  //      }
   //     printf("\n");
   // }

    return;


}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //la question ici c'est de savoir si la structure de data c'est une paire = un vainqueur et un perdant
    //et dans ce cas-là je ne comprends pas où mettre la pondération
    //ou si on a une paire, par exemple A vs B, et que si A - B est 6 fois mais que B - A est 12 fois
    // bah B remporte
    pair_count = 0;
    
    for (int i = 0; i <= candidate_count; i++)
    {
        for (int j = 0; j <= candidate_count; j++)
        {
            if ( i != j && preferences[i][j] != 0)
            {
                if (preferences[i][j] > preferences[j][i]) 
                {
                    
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
                }
            };
        }
    }
    
   // printf("le numéro de paires: %i\n", pair_count);
   // printf("la 1: %i - %i\n", pairs[0].winner, pairs[0].loser);
   // printf("la 2eme: %i - %i\n", pairs[1].winner, pairs[1].loser);
   // printf("la 3eme: %i - %i\n", pairs[2].winner, pairs[2].loser);
   // printf("la 4eme: %i - %i\n", pairs[3].winner, pairs[3].loser);
   // printf("la 5eme: %i - %i\n", pairs[4].winner, pairs[4].loser);
   // printf("la 6eme: %i - %i\n", pairs[5].winner, pairs[5].loser);
   // printf("\n");

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    
    //donc la techniquement j'ai ma paire par avoir le int de l'un et de l'autre
    //partant de ma paire, peut-être que je peux avoir le chiffre de victoire correspondant
    //parce que le int winner va être mon i dans preferences et mon j va être mon perdant
    
    int x = 0;
    int temp_valuewinner = 0;
    int temp_valueloser = 0;
    int swap = 0;
    

    for (x = 0; x <= pair_count; x++)
    {
        int initial_winner = pairs[x].winner;
        int initial_loser = pairs[x].loser;
        
        for (int y = x + 1; y <= pair_count; y++ )
        {
            if (preferences[pairs[x].winner][pairs[x].loser] < preferences[pairs[y].winner][pairs[y].loser] ) 
             {
              initial_winner = pairs[y].winner;
              initial_loser = pairs[y].loser;
              pairs[y].winner = pairs[x].winner;
              pairs[y].loser = pairs[x].loser;
              pairs[x].winner = initial_winner;
              pairs[x].loser = initial_loser;
              swap++;
             }
             
        }
        
    }
    
   // for (int y = 0; y < pair_count; y++) {
    //    printf("Sorted winner : %d \n", pairs[y].winner);
    //    printf("Sorted loser : %d \n", pairs[y].loser);
    //}
    printf("\n");
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //ici on retourne vrai quand une fonction est pairs d'avant
    // et surtout quand cette fonction ne fait pas une boucle
    // mais comment est-ce qu'on caractérise une boucle? 
    
   
    
    for (int i = 0; i <= pair_count; i++)
    {
       
      locked[pairs[i].winner][pairs[i].loser] = true;
      
      check_cycle(pairs[i].winner,pairs[i].loser);
      
      if (check_cycle(pairs[i].winner,pairs[i].loser) == true)
      {
          locked[pairs[i].winner][pairs[i].loser] = false;
          
      }
      
      
      
    }
    
    
   // printf("liste des locked\n");
    
   //  for (int mich = 0; mich < candidate_count; mich++)
   // {
    //    for (int aba = 0; aba < candidate_count; aba++)
   //     {
    //        if (locked[mich][aba] == true) {
    //        printf("locked [%i][%i]\n", mich, aba);
   //         }
    //    }
   // }
   // printf("liste des locked par préférences\n");
    
   // for (int bleu = 0; bleu < pair_count; bleu++)
   // {
   //     printf("La vraie liste des lockés %i - %i\n", pairs[bleu].winner, pairs[bleu].loser);
   // }
   // for (int rouge = 0; rouge < candidate_count; rouge++) {
   //     for (int vert = 0; vert < candidate_count; vert++) {
   //         printf("%i ", locked[rouge][vert]);
  //      }
   //     printf("\n");
   // }
    
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int liste_de_j[pair_count];
    int nombre = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count - 1; j++)
        {
            if (locked[i][j] == true)
            {
                liste_de_j[nombre] = j;
                nombre++;
            }
        }
    }
    
    
    // là c'est juste un espace
    //printf("\n bon là on va examiner l'array de liste de j\n");
    
    //for (int bite = 0; bite < pair_count; bite++)
    //{
    //    printf("%i\n", liste_de_j[bite]);
   // }
    
    
    for (int p = 0; p < candidate_count; p++)
    {
        if (is_in_the_array(liste_de_j, p) == false )
        {
            printf("%s\n", candidates[p]);
            return;
        }
    }
    return;
}

bool check_cycle(int a, int b)
{
    if (locked[b][a] == true)
    {
        return true;
    }
    
    for (int i = 0; i <= candidate_count; i++)
    {
        if (locked[i][a] == true) {
        
        return check_cycle(i, b);
        }
    }
    
    return false;
}

bool is_in_the_array(int liste_de_j[], int a) 
{
    int x = 0;
    for (x = 0; x < pair_count; x++) 
    {
            if (liste_de_j[x] == a)
            {
                return true;
            }

    }
    return false;
}