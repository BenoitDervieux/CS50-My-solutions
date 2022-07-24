#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
    
    char name[MAX_NAME];
    int age;
    //..... add other stuff
}person;


person * hash_table[TABLE_SIZE];


unsigned int hash(char *name) {
    
    int length = strlen(name);
    unsigned int hash_value = 0;
    for (int i=0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    
    return hash_value;
}



void init_hash_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    //table is empty
}

void print_table() {
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }else if (hash_table[i] == DELETED_NODE) {
            printf("\t%i\t---<deleted>\n",i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("End\n");
}

bool hash_table_insert(person *p)
{
    if (p == NULL) return false;
    int index = hash(p->name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE)
        {
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

person *hash_table_lookup (char *name)
{
    int index = hash(name);
    for (int i=0; i<TABLE_SIZE; i++) 
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) {
            return false; //not here
        }
        if (hash_table[try] == DELETED_NODE) return NULL;
        
        if (hash_table[try] != NULL &&
        strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0) {
            return hash_table[try];
        }
    }
    return NULL;
}

person *hash_table_delete(char *name)
{
    int index = hash(name);
    for (int i=0; i < TABLE_SIZE; i++) 
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) return NULL;
        if (hash_table[try] == DELETED_NODE) continue;
        if (strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0) {
            
            person* tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
    return NULL;
}

int main() {
    
    init_hash_table();
    
    person jacob = {.name="Jacob", .age = 26};
    person Kate = {.name="Kate", .age = 27};
    person Mpho = {.name="Mpho", .age = 14};
    person sarah = {.name="sarah", .age = 54};
    person edna = {.name="edna", .age = 15};
    person maren = {.name="maren", .age = 25};
    person eliza = {.name="eliza", .age = 34};
    person robert = {.name="robert", .age = 1};
    person jane = {.name="jane", .age = 75};
    
    hash_table_insert(&jacob);
    hash_table_insert(&Kate);
    hash_table_insert(&Mpho);
    hash_table_insert(&sarah);
    hash_table_insert(&edna);
    hash_table_insert(&maren);
    hash_table_insert(&eliza);
    hash_table_insert(&robert);
    hash_table_insert(&jane);
    
    print_table();
    
    person *tmp = hash_table_lookup("Mpho");
    
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s\n", tmp->name);
    }
    
    
    tmp = hash_table_lookup("George");
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s\n", tmp->name);
    }
    
    hash_table_delete("Mpho");
    tmp = hash_table_lookup("Mpho");
    
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s\n", tmp->name);
    }
    print_table();
    
    return 0;
}