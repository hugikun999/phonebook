#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "phonebook_hash.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName_hash(char lastName[], Hash_Table *hash_head)
{
    entry *check = hash_head->pHead;

    while(check != NULL) {
        if(strcasecmp(lastName, check->lastName) == 0)
            return check;
        else
            check = check->pNext;
    }
    return NULL;
}

void append_hash(char lastName[], Hash_Table *hash_head)
{
    if(hash_head->pHead == NULL) {
        hash_head->pHead = (entry *) malloc(sizeof(entry));
        hash_head->pLast = hash_head->pHead;
        hash_head->pLast->pNext = NULL;
        strcpy(hash_head->pLast->lastName, lastName);
    } else {
        hash_head->pLast->pNext = (entry *) malloc(sizeof(entry));
        hash_head->pLast = hash_head->pLast->pNext;
        hash_head->pLast->pNext = NULL;
        strcpy(hash_head->pLast->lastName, lastName);
    }
}

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}
