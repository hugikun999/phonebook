#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "phonebook_hash.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
bool findName_hash(char lastName[], hash_table *hash_head, unsigned int hash_value)
{
    hash_table *hash;
    hash = hash_head;

    while(1) {
        if(hash->hash_value == NULL)
            return false;
        else if(*hash->hash_value != hash_value) {
            if(hash->pNext != NULL)
                hash = hash->pNext;
            else
                return false;
        } else {
            entry *test = hash->eHead;
            while(1) {
                if(strcasecmp(lastName, test->lastName) == 0)
                    return true;
                else {
                    if(test->pNext != NULL)
                        test = test->pNext;
                    else
                        return false;
                }
            }
        }
    }
}

void append_hash(char lastName[], hash_table *hash_head, unsigned int hash_value)
{
    hash_table *hash;
    hash = hash_head;
    while(1) {
        if(hash->hash_value == NULL) {
            hash->hash_value = (unsigned int *) malloc(sizeof(unsigned int));
            *hash->hash_value = hash_value;
            hash->e = (entry *) malloc(sizeof(entry));
            hash->eHead = hash->e;
            strcpy(hash->e->lastName, lastName);
            hash->e->pNext = NULL;
            break;
        } else if(*hash->hash_value != hash_value) {
            if(hash->pNext != NULL) {
                hash = hash->pNext;
            } else {
                hash->pNext = (hash_table *) malloc(sizeof(hash_table));
                hash = hash->pNext;
                hash->hash_value = (unsigned int *) malloc(sizeof(unsigned int));
                *hash->hash_value = hash_value;
                hash->pNext = NULL;
                hash->e = (entry *) malloc(sizeof(entry));
                hash->eHead = hash->e;
                strcpy(hash->e->lastName, lastName);
                hash->e->pNext = NULL;
                break;
            }

        } else {
            hash->e->pNext = (entry *) malloc(sizeof(entry));
            hash->e = hash->e->pNext;
            strcpy(hash->e->lastName, lastName);
            hash->e->pNext = NULL;
            break;
        }
    }

    return;
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
