#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "phonebook_opt.h"

static entry *record;
static int branch = 0;

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastName[], entry *pHead)
{
    pHead = pHead->pNext;

    while (pHead != NULL) {
        if(lastName[0] == pHead->lastName[0]) {
            if (strcasecmp(lastName, pHead->lastName) == 0)
                return pHead;
            pHead = pHead->pNext;
        } else
            pHead = pHead->pOther;
    }

    return NULL;
}

entry *append(char lastName[], entry *e)
{
    if(branch == 0) {
        e->pNext = (entry *) malloc(sizeof(entry));
        e = e->pNext;
        strcpy(e->lastName, lastName);
        e->pNext = NULL;
        e->detail = (detail *) malloc(sizeof(detail));
        branch++;
        record = e;
        return e;
    } else if(e->lastName[0] == lastName[0]) {
        e->pNext = (entry *) malloc(sizeof(entry));
        e = e->pNext;
        e->detail = (detail *) malloc(sizeof(detail));
        strcpy(e->lastName, lastName);
        return e;
    } else {
        e = record;
        e->pOther = (entry *) malloc(sizeof(entry));
        e = e->pOther;
        strcpy(e->lastName, lastName);
        e->pNext = NULL;
        e->detail = (detail *) malloc(sizeof(detail));
        record = e;
        return e;
    }
}
