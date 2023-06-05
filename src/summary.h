#ifndef SUMMARY_H_ 
#define SUMMARY_H_

#include <stdio.h>
#include "types.h"

int numberOfNotDeletedCrypto(TArrayOfCrypto *crypto);

int averageFoundationYear(TArrayOfCrypto *crypto);

int oldest(TArrayOfCrypto *crypto);

int youngest(TArrayOfCrypto *crypto);

void summary(TArrayOfCrypto *crypto);

void foundedBeforeYear(TArrayOfCrypto *crypto);

#endif
