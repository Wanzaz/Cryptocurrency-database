/*
#
 * Types
 *
 * */


#ifndef TYPES_H
#define TYPES_H


#define BLOCK 32
#define MAXN 100

/*
 * Formats of single cryptoccurency entity
 * */
#define DATA_FORMAT "%d %d %s %s %d %d %d\n"

#include<stdbool.h>


/* 
 * Representation of cryptoccurency entity
 * */
typedef struct _cryptocurrency {
    int id;
    int foundation_year;
    char name[41];
    char founder_name[41];
    float price;
    bool centralized;
    bool deleted;
} TCryptocurrency;


/* 
 * Represents array of cryptoccurency entities
 * */
typedef struct _array {
    TCryptocurrency *value;
    int lenght;
    int capacity;
} TArrayOfCrypto;


/*
 * Represents one item for menu
 * */
typedef struct {
    char* description;
    int (*function)(TArrayOfCrypto* list);
} Taction;


/*
 * Helps the sorting function to be generic
 * */
typedef enum _CompareType
{
    ById,
    ByFoundationYear,
    ByName,
    ByFounderName,
    ByPrice,
    ByCentralization,
} CompareType;


/* typedef enum { */
/*     FILE_ERROR = -1, */
/*     LOADING_DATA_ERROR = -2, */
/*     DATABASE_DATA_FORMAT_ERROR = -3, */
/*     USER_OPTION_ERROR = -4, */
/*     LOADING_FORMAT_INPUT = -5, */
/*     ARGS_ERROR = -6, */
/* } Terrorhandling; */

#endif
