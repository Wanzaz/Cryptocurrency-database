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
#define DATA_FORMAT "%d %d %40s %40s %f %d\n"
#define PRINT_DATA_FORMAT "%d %d %s %s %f %d\n"
#define PRETTY_FORMAT "| %2d | %15d | %13s | %17s | %9.2f |\n"
#define INPUT_FORMAT "%d %40[^\n] %40[^\n] %f\n"


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
    bool deleted;
} TCryptocurrency;


/* 
 * Represents array of cryptoccurency entities
 * */
typedef struct _array {
    TCryptocurrency *value;
    int lenght;
} TArrayOfCrypto;


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
