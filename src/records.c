#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "records.h"
#include "helpers.h"
#include "lists.h"
#include "comparing.h"

// kontrolovat maximum pole pri pridani prvku
void addRecord(FILE *output, TArrayOfCrypto *crypto)
{
    /* TCryptocurrency new_cryptocurrency; */
    /* printf("[INSTRUCTION]: Enter info in format: foundation_year name founder_name price\n"); */
    /* if (loadOneCrypto(stdout, &new_cryptocurrency) == 0) { */

    /*     crypto->value[crypto->lenght] = new_cryptocurrency; */
    /*     crypto->lenght++; */

    /*     printf("[INFO]: Record was successfully added.\n\n\n"); */
    /*     writeCryptocurrencies(output, crypto); */
        
    /* } else { */
    /*     printf("[ERROR]: Information in a wrong format.\n"); */
    /* } */
}

void changeRecord(FILE *output, TArrayOfCrypto *crypto)
{
    int index;
    writeCryptocurrencies(stdout, crypto);

    printf("\n\n[INSTRUCTION]: Enter record index which you wanna change: \n");
    scanf("%d", &index);

    if (index >= 0 && index < crypto->lenght) {
        TCryptocurrency new_cryptocurrency;
        printf("[INSTRUCTION]: Enter info in format: foundation_year name founder_name price\n");

        if (loadOneCrypto(stdout, &new_cryptocurrency) == 0) {
            crypto->value[index] = new_cryptocurrency;

            printf("[INFO]: Record was successfully changed.\n\n\n");
            writeCryptocurrencies(output, crypto);
        } else {
            printf("[ERROR]: Information in a wrong format.\n");
        }

    } else {
        printf("[ERROR]: Wrong index.\n");
    }
}

int removeBackup(TArrayOfCrypto *crypto, char inputpath[])
{
    FILE *database = fopen(inputpath, "w");
    if (database == NULL) return -1;

    for (int i = 0; i < crypto->lenght; i++) {
        printOneCrypto(database, crypto->value[i]);
    }

    fclose(database);
    return 0;
}

// vyhledavat a pak smazat
void removeRecord(FILE *output, TArrayOfCrypto *crypto, char inputpath[])
{
    int index;
    writeCryptocurrencies(stdout, crypto);

    printf("\n\n[INSTRUCTION]: Enter record index which you wanna delete: \n");
    scanf("%d", &index);

    if (index >= 0 && index < crypto->lenght) {
        for (int i = index; i < crypto->lenght - 1; i++) {
            crypto->value[i] = crypto->value[i + 1];
        }

        crypto->lenght--;
        printf("[INFO]: Record was successfully deleted.\n\n\n");
        writeCryptocurrencies(output, crypto);
    
    } else {
        printf("[ERROR]: Wrong index.\n");
    }

    removeBackup(crypto, inputpath);
}


void searchByName(TArrayOfCrypto *crypto)
{
    int found = 0;
    char searched_name[41];
    printf("[INSTRUCTION]: Enter a name of searched cryptocurrency: \n");
    scanf("%40s", searched_name);

    for (int i = 0; i < crypto->lenght; i++) {
        if (strcmp(crypto->value[i].name, searched_name) == 0) {
            printOneCrypto(stdout, crypto->value[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("[ERROR]: Item wasn't found.\n");
    }
}

void dataBackup(FILE *output, TArrayOfCrypto *crypto)
{
    printf("[INFO]: Data were successfully backed up.\n");
    writeCryptocurrencies(output, crypto);
}
