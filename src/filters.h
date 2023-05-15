#ifndef FILTERS_H_
#define FILTERS_H_

#include <stdio.h>
#include "types.h"


int averageFoundationYear(TArrayOfCrypto *crypto);

int oldest(TArrayOfCrypto *crypto);

int youngest(TArrayOfCrypto *crypto);

void summary(TArrayOfCrypto *crypto);

void foundedBeforeYear(FILE *output, TArrayOfCrypto *crypto, int before_year);

void beforeYear(FILE *output, TArrayOfCrypto *crypto);

#endif
