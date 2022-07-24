#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string sentence = get_string("Text: ");
    
    int letters = 0;
    
    int words = 1;
    
    int dots = 0;
    
    float L = 0;
    
    float S = 0;
    
    float index = 0;
    
    int index_int = 0;
    
    //unsigned long i = strlen(sentence);
    
    for (int i = 0; i < strlen(sentence); i++)
    {
        if ( (64 < sentence[i] && sentence[i] < 91) || (96 < sentence[i] && sentence[i] < 123) )
        {
            letters++;
        }
        
        if (sentence[i] == 32)
        {
            words++;
        }
        
        if (sentence[i] == 33 || sentence[i] == 46 || sentence[i] == 63)
        {
            dots++;
        }
        
    }
    
    L = (float) letters*100/words;
    S = (float) dots*100/words;
    
    index = 0.0588 * L - 0.296 * S - 15.8;
    
    index_int = round(index);
    
    if (index_int < 1 )
    {
        printf("Before Grade 1\n");
    }
    else if (index_int > 1 && index_int < 16)
    {
        printf("Grade %i\n", index_int);
    }
    else if (index_int >= 16)
    {
       printf("Grade 16+\n"); 
    }
    
    /*printf("\n\n##################\n\n");
    printf("%i letter(s)\n", letters);
    printf("%i word(s)\n", words);
    printf("%i sentence(s)\n", dots);
    printf("%f L\n", L);
    printf("%f S\n", S);
    printf("%f S\n", index);
    printf("Index: %i\n", index_int);*/
    
}