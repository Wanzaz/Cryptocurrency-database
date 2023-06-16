#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "records.h"
#include "helpers.h"
#include "lists.h"


int highestID(TArrayOfCrypto *crypto)
{
    int highest = 0;
    for (int i = 0; i < crypto->lenght; i++) {
        if (crypto->value[i].id > highest && !crypto->value[i].deleted) {
            highest = crypto->value[i].id;
        }
    }
    return highest;
}

void addRecord(FILE *output, TArrayOfCrypto *crypto)
{
    TCryptocurrency new;
    printf("[INSTRUCTION]: Enter info in format: foundation_year name founder_name price\n");
    clearBuffer();
    if (loadOneCryptoInput(stdin, &new, INPUT_FORMAT) == 4 && crypto->lenght < MAXN) {
        crypto->value[crypto->lenght] = new;
        crypto->value[crypto->lenght].id = highestID(crypto) + 1;
        crypto->value[crypto->lenght].deleted = false;
        crypto->lenght++;

        printHead();
        writeOne(output, crypto->value[crypto->lenght - 1], PRETTY_FORMAT);
        printTail();
        printf("[INFO]: Record was successfully added.\n\n\n");
        
    } else {
        printf("[ERROR]: Information in a wrong format.\n");
    }
}

void changeRecord(FILE *output, TArrayOfCrypto *crypto)
{
    TCryptocurrency new;
    char searched_name[41];
    char answer;
    int old_id;

    printf("[INSTRUCTION]: Enter a name of searched cryptocurrency that you want to CHANGE: \n");
    clearBuffer();
    scanf("%40s", searched_name);

    int *found = arrayOfSearchedNameIndexes(crypto, searched_name);
    if (found[0] != 0) {
        for (int i = 0; found[i] != 0; i++) {
            clear();
            printf("Do you wanna change this record? (y/n)\n");
            printHead();
            writeOne(stdout, crypto->value[found[i] - 1], PRETTY_FORMAT);
            printTail();

            printf("[INSTRUCTION]: Enter your answer: ");
            clearBuffer();
            scanf("%c", &answer);

            if (answer == 'y') {
                printf("[INSTRUCTION]: Enter info in format: foundation_year name founder_name price\n");
                if (loadOneCryptoInput(stdin, &new, INPUT_FORMAT) == 4 && crypto->lenght < MAXN) {
                    old_id = crypto->value[found[i] - 1].id;
                    crypto->value[found[i] - 1] = new;
                    crypto->value[found[i] - 1].deleted = false;
                    crypto->value[found[i] - 1].id = old_id;

                    printHead();
                    writeOne(output, crypto->value[found[i] - 1], PRETTY_FORMAT);
                    printTail();
                    printf("\n[INFO]: Record was successfully changed.\n\n\n");
                    
                } else {
                    printf("[ERROR]: Information in a wrong format.\n");
                }
            }
        }
    } else {
        printf("[ERROR]: Item wasn't found.\n");
    }

    free(found);

}


void removeRecord(FILE *output, TArrayOfCrypto *crypto, char inputpath[])
{
    char searched_name[41];
    char answer;

    printf("[INSTRUCTION]: Enter a name of searched cryptocurrency that you want to DELETE: \n");
    scanf("%40s", searched_name);

    int *found = arrayOfSearchedNameIndexes(crypto, searched_name);
    if (found[0] != 0) {
        for (int i = 0; found[i] != 0; i++) {
            clear();
            printf("Do you wanna delete this record? (y/n)\n");
            printHead();
            writeOne(stdout, crypto->value[found[i] - 1], PRETTY_FORMAT);
            printTail();

            printf("[INSTRUCTION]: Enter your answer: ");
            clearBuffer();
            scanf("%c", &answer);

            if (answer == 'y') {
                crypto->value[found[i] - 1].deleted = true;
                printf("\n[INFO]: Record was successfully deleted.\n\n\n");
            }
        }
    } else {
        printf("[ERROR]: Item wasn't found.\n");
    }

    free(found);
}

void fillArrayWithZeroes(int *array, int lenght)
{
    for (int i = 0; i < lenght; i++) {
        array[i] = 0;
    }
}

int *arrayOfSearchedNameIndexes(TArrayOfCrypto *crypto, char searched_name[])
{
    int *found = malloc(crypto->lenght * sizeof(int));
    fillArrayWithZeroes(found, crypto->lenght);

    if (!found) {
        printf("[ERROR]: Couldn't allocate memory.\n");
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < crypto->lenght; i++) {
        if (strcmp(crypto->value[i].name, searched_name) == 0 && !crypto->value[i].deleted) {
            found[j] = i + 1;
            j++;
        }
    }

    return found;
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

void dataBackup(FILE *output, TArrayOfCrypto *crypto, char inputpath[])
{
    FILE *backup = fopen(inputpath, "w");
    if (backup == NULL) {
        printf("[ERROR]: Couldn't open file.\n");
        return;
    }

    writeAll(backup, crypto, PRINT_DATA_FORMAT);
    printf("[INFO]: Data were successfully backed up.\n");
    fclose(backup);
    print(crypto);
}
