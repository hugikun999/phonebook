#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* line to set OPT properly */

typedef struct __attribute__ ((__packed__)) __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
    struct __PHONE_BOOK_DETAIL *detail;
    struct __PHONE_BOOK_ENTRY *pOther;
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

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif
