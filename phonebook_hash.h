#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

#include <stdbool.h>

typedef struct __attribute__ ((__packed__)) __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
    struct __PHONE_BOOK_DETAIL *detail;
} entry;

typedef struct __attribute__ ((__packed__))  __PHONE_BOOK_DETAIL {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail;

typedef struct __HASH_TABLE {
    entry *pHead;
    entry *pLast;
} Hash_Table;

entry *findName_hash(char lastName[], Hash_Table *hash_head);
void append_hash(char lastName[], Hash_Table *hash_head);
unsigned int BKDRHash(char *str);

#endif
