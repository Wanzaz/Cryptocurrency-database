#ifndef LISTS_H_
#define LISTS_H_

#include <stdio.h>
#include "types.h"

#define MAXN 100
#define BlOCK 32

int loadOneCrypto(FILE *input, TCryptocurrency *cryptocurrency, char* format);

TArrayOfCrypto * loadCryptocurrencies(FILE *file);

void write(FILE* output, TArrayOfCrypto *crypto, char* format);

void printHead();

void printTail();

int print(TArrayOfCrypto* crypto);

void writeOne(FILE *file, TCryptocurrency cryptocurrency, char* format);


// function to swap elements
void swap(TCryptocurrency array[], int x, int y);

// function to find the partition position
static inline
int partition(TCryptocurrency array[], int start, int end, CompareType type);

void quickSort(TCryptocurrency array[], int start, int end, CompareType type);

bool isSortedByFoundationYear(TArrayOfCrypto *crypto);

void sort(FILE *output, TArrayOfCrypto *crypto, CompareType type);

#endif
