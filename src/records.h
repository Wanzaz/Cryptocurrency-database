#ifndef RECORDS_H_
#define RECORDS_H_

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void addRecord(FILE *output, TArrayOfCrypto *crypto);

void changeRecord(FILE *output, TArrayOfCrypto *crypto);

int removeBackup(TArrayOfCrypto *crypto, char inputpath[]);

void removeRecord(FILE *output, TArrayOfCrypto *crypto, char inputpath[]);

void searchByName(TArrayOfCrypto *crypto);

void dataBackup(FILE *output, TArrayOfCrypto *crypto);

#endif
