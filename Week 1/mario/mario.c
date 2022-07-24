#include <cs50.h>
#include <stdio.h>


int get_positive_int(void);

int main(void)
{
    int j = get_positive_int();
    
    for (int i = 1; i <= j; i++) {
        
        int k = 0;
        while(k < j - i)
        {
            printf(" ");
            k++;
        }
        
        for (int p = 1; p <= i; p++){
            printf("#");
        }
        
        printf("  ");
        
        for (int x = 1; x <= i; x++){
            printf("#");
        }
        
        printf("\n");
    }

}

int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8 );
    return n;
}