#include <cs50.h>
#include <stdio.h>
#include <string.h>

//int main (void) 
//{
//    int numbers[] = {4, 6, 8, 2, 7, 5, 0};
//    
//    for (int i = 0; i < 7; i++)
//    {
//        if (numbers[i] == 0)
//         {
//             printf("Found\n");
//             return 0;
//         }
//    }
//    printf("Not found\n");
//    return 1;
//};

//int main(void)
//{
//    string names[] = {"Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"};
    
//    for (int i = 0; i < 7; i++)
//    {
//        if (strcmp(names[i], "Ron") == 0)
//        {
//            printf("Found\n");
//            return 0;
//        }
//    }
    
//    printf("Not found\n");
//    return 1;
//};

typedef struct
{
    string name;
    string number;
}
person;

int main (void)
{
   person people[2];
   
   people[0].name = "Brian";
   people[0].number = "+1-617-495-1000";
   
   people[1].name = "David";
   people[1].number = "+1-949-468-2750";
    
    for (int i = 0; i <2; i++)
    {
        if (strcmp(people[i].name, "David") == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}


