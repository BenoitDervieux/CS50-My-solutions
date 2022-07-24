// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[45];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

int numberOfWords = - 1;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashedToCheck = 0;

    hashedToCheck = hash(word);

    
    for (node *cursor = table[hashedToCheck]; cursor != NULL; cursor = cursor->next)
    {
        
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
        
        // Source of the hash table: http://www.cse.yorku.ca/~oz/hash.html
        unsigned int hash = 5381;
        int c = 0;

        while ((c = *word++)) 
        {
            
            if (64 < c && c < 91 )
            { 
                c = c + 32; 
                
            }
            
            hash = ((hash << 5) + hash) ^ c; /* hash * 33 + c */
        }
            
        hash = hash % N;

        return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //int sizeWord = strlen(*dictionary);
    char wordSpace[46] = {0};
    int index = 0;
    int numberWords = -1;
    
    FILE *readDict = fopen(dictionary, "r");
    if (readDict == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    while (fscanf(readDict, "%s", wordSpace) != EOF)
    {
        index = 0;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
        return 1;
        }
        strcpy(n->word, wordSpace);
        
        n->next = NULL;
        
        index = hash(n->word);
        
        n->next = table[index];
        
        table[index] = n;
        
        numberWords = size();

    }
    
    fclose(readDict);
    
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    numberOfWords++;
    return numberOfWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    
    node *cursor = NULL;
    node *tmp = NULL;
    
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        
            while (cursor != NULL)
            {
                tmp = cursor;
                cursor = cursor->next;
                free(tmp);
            }
        free(cursor);

    }
    
    return true;
}
