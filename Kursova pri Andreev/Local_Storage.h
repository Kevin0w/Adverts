#ifndef LOCAL_STORAGE_H_INCLUDED
#define LOCAL_STORAGE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 30

typedef struct Advert{
    char type[MAX_SIZE];
    char id[MAX_SIZE];
    char title[MAX_SIZE];
    double price;
}sAdvert_t;

typedef struct List{
    sAdvert_t payload;
    struct List *next;
}sList_t;


sList_t *readFromRequestFile(FILE *, sList_t *);
sList_t *readFromSellFile(FILE *, sList_t *);
void checkForMatchings(sList_t *, sList_t *);
void deleteAdvert(sList_t *, sList_t *);
void freeList(sList_t *, sList_t *);
void printAllElements(sList_t *, sList_t *);
void write_req_el(sList_t *);
void write_sell_el(sList_t *);



#endif // LOCAL_STORAGE_H_INCLUDED
