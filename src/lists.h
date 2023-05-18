#ifndef LISTS_H_
#define LISTS_H_

#include <stdio.h>
#include "types.h"

#define MAXN 100
#define BlOCK 32

int loadOneCrypto(FILE *input, TCryptocurrency *cryptocurrency);

TArrayOfCrypto * loadCryptocurrencies(FILE *file);

void printOneCrypto(FILE *file, TCryptocurrency cryptocurrency);

void writeCryptocurrencies(FILE *output, TArrayOfCrypto *crypto);

// function to swap elements
void swap(TCryptocurrency array[], int x, int y);

// function to find the partition position
static inline
int partition(TCryptocurrency array[], int start, int end, CompareType type);

void quickSort(TCryptocurrency array[], int start, int end, CompareType type);

bool isSortedByFoundationYear(TArrayOfCrypto *crypto);

void sort(FILE *output, TArrayOfCrypto *crypto, CompareType type);

#endif
