#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    
    if (argc == 2) 
    {
        int n = strlen(argv[1]);
        
        if (n == 26)
        {
            
            for (int i = 0; i < n; i++)
            {
                if (isalpha(argv[1][i]) == 0)
                {
                printf("Your input is non-alphabetical.\n");
                return 1;
                }
                else
                {
                  for (int j = 0; j < n; j++)
                  {
                      if ((argv[1][i]) == (argv[1][j]) && j != i )
                      {
                          return 1;
                      }
                  }
                   
                }
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    //Ask for the input here
    
    string input = get_string("plaintext: ");
    
    int longueurInput = strlen(input);
    
    for (int p = 0; p < longueurInput; p++)
        {
            int enNombre = input[p];
            int valeurDeKey = '\0';
            
            if (enNombre > 64 && enNombre < 91 )
            {
                valeurDeKey = enNombre - 65;
                input[p] = argv[1][valeurDeKey];
                char convert = input[p];
                input[p] = toupper(convert);
            }
            else if (enNombre > 96 && enNombre < 123 )
            {
                valeurDeKey = enNombre - 97;
                input[p] = argv[1][valeurDeKey];
                char convert = input[p];
                input[p] = tolower(convert);
            }
        }
        
        printf("ciphertext: %s\n", input);
    
}