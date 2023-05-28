#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "records.h"
#include "helpers.h"
#include "lists.h"
#include "comparing.h"

void addRecord(FILE *output, TArrayOfCrypto *crypto)
{
    TCryptocurrency new;
    printf("[INSTRUCTION]: Enter info in format: foundation_year name founder_name price\n");
    if (loadOneCrypto(stdout, &new, INPUT_FORMAT) == 4 && crypto->lenght < MAXN) {

        crypto->value[crypto->lenght] = new;
        crypto->lenght++;

        printf("[INFO]: Record was successfully added.\n\n\n");
        write(stdout, crypto, PRETTY_FORMAT);
        
    } else {
        printf("[ERROR]: Information in a wrong format.\n");
    }
}

void changeRecord(FILE *output, TArrayOfCrypto *crypto)
{
    /* int index; */
    /* writeCryptocurrencies(stdout, crypto); */

    /* printf("\n\n[INSTRUCTION]: Enter record index which you wanna change: \n"); */
    /* scanf("%d", &index); */

    /* if (index >= 0 && index < crypto->lenght) { */
    /*     TCryptocurrency new_cryptocurrency; */
    /*     printf("[INSTRUCTION]: Enter info in format: foundation_year name founder_name price\n"); */

    /*     if (loadOneCrypto(stdout, &new_cryptocurrency) == 0) { */
    /*         crypto->value[index] = new_cryptocurrency; */

    /*         printf("[INFO]: Record was successfully changed.\n\n\n"); */
    /*         writeCryptocurrencies(output, crypto); */
    /*     } else { */
    /*         printf("[ERROR]: Information in a wrong format.\n"); */
    /*     } */

    /* } else { */
    /*     printf("[ERROR]: Wrong index.\n"); */
    /* } */
}


void removeRecord(FILE *output, TArrayOfCrypto *crypto, char inputpath[])
{
    char searched_name[41];
    printf("[INSTRUCTION]: Enter a name of searched cryptocurrency that you want to deleted: \n");
    scanf("%40s", searched_name);

    int index = searchByNameReturnIndex(crypto, searched_name);
    if (index != -1) {
        crypto->value[index].deleted = 1;
        printf("[INFO]: Record was successfully deleted.\n\n\n");
        write(stdout, crypto, PRETTY_FORMAT);
    } else {
        printf("[ERROR]: Item wasn't found.\n");
    }
}

int searchByNameReturnIndex(TArrayOfCrypto *crypto, char searched_name[])
{
    for (int i = 0; i < crypto->lenght; i++) {
        if (strcmp(crypto->value[i].name, searched_name) == 0 && !crypto->value[i].deleted) {
            return i;
        }
    }
    return -1;
}

void searchByName(TArrayOfCrypto *crypto)
{
    int found = 0;
    char searched_name[41];
    printf("[INSTRUCTION]: Enter a name of searched cryptocurrency: \n");
    scanf("%40s", searched_name);

    printHead();
    for (int i = 0; i < crypto->lenght; i++) {
        if (strcmp(crypto->value[i].name, searched_name) == 0 && !crypto->value[i].deleted) {
            writeOne(stdout, crypto->value[i], PRETTY_FORMAT);
            found++;
        }
    }
    printTail();

    if (found == 0) {
        printf("[ERROR]: Item wasn't found.\n");
    }
}

void dataBackup(FILE *output, TArrayOfCrypto *crypto)
{
    /* printf("[INFO]: Data were successfully backed up.\n"); */
    /* writeCryptocurrencies(output, crypto); */
}
