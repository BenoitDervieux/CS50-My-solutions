#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long cardNumber = get_long("Number: ");
    
    int i = 0;
    int sum=0;
    int digitToAdd;
    int stockDebut;
    int firstNumber;
    bool card = false;
    int resultModuloSum;
    int checkSum;
    
    while(cardNumber > 0 )
    {
        digitToAdd = 0;
        //ici on va prendre le grand nombre et en faire le modulo
        digitToAdd = cardNumber % 10;
        
        i++;
        
        cardNumber /= 10;
        
        if( i % 2 == 0) 
        {
            digitToAdd *= 2;
            if (digitToAdd > 9) 
             {
                 digitToAdd = (digitToAdd % 10) + 1;
             }
        }
        
        if (cardNumber > 9 && cardNumber < 100 )
        {
            stockDebut = cardNumber;
        }
        
        if (cardNumber > 0 && cardNumber < 10)
        {
            firstNumber = cardNumber;
        }
        
        sum = sum + digitToAdd;
        
        
        

    }
    
     checkSum = sum % 10;
     
            if (checkSum == 0) 
        {
            card = true;
        }

    
    if ( i == 13 && firstNumber == 4 && card == true ) 
    {
        printf("VISA\n");
        
    } else if (i == 15 && (stockDebut == 37 || stockDebut == 34) && card == true ) {
        
        printf("AMEX\n");
        
    } else if ( i == 16 && firstNumber == 4 && card == true ) {
        
        printf("VISA\n");
        
    } else if (i == 16 && stockDebut >50 && stockDebut <56 && card == true) {
        
        printf("MASTERCARD\n");
        
        
    } else {
        
        printf("INVALID\n");
    }
}