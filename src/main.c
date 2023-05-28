#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // for work with text strings
#include <stdbool.h> // for work with type of bool and constants true and false
#include "types.h"
#include "filters.h"
#include "records.h"
#include "helpers.h"
#include "lists.h"


// TODO 
// - enum for error returns
// - error with wrong format
// - make it more generic
// - optimize algorithm for searching
// - add capacity to dynamic array



int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("[ERROR]: Program should be executed like this:\n"
               "\t./a.out inputfile\n");
        return -1;
    }

    char *inputpath = argv[1];
    FILE *database = fopen(inputpath, "r+");
    if (database == NULL) return -1;


    // Warning a user if the data were unsuccessfully loaded from the database
    TArrayOfCrypto * crypto = loadCryptocurrencies(database);
    if (crypto == NULL) return -2;

    int choice = 1;
    while (choice != -4) {
        mainMenu();

        int choice = checkingForUserChoice();
        
        switch(choice) {
            case 0: clear();
                exitProgram();
            case 1: clear();
                print(crypto);
                break;
            case 2: clear();
                addRecord(stdout, crypto);
                break;
            case 3: clear();
                changeRecord(stdout, crypto);
                break;
            case 4: clear();
                removeRecord(stdout, crypto, inputpath);
                break;
            case 5: clear();
                searchByName(crypto);
                break;
            case 6: clear();
                sort(stdout, crypto, ByFoundationYear);
                break;
            case 7: clear();
                sort(stdout, crypto, ByName); 
                break;
            case 8: clear();
                sort(stdout, crypto, ByFounderName); 
                break;
            /* case 9: clear(); */
            /*     sort(stdout, crypto, ByPrice); */ 
            /*     break; */
            case 10: clear();
                sort(stdout, crypto, ById);
                break;
            case 11: clear();
                 foundedBeforeYear(crypto);
                break;
            case 12: clear();
                 summary(crypto);
                break;
            case 13: clear();
                 dataBackup(database, crypto);
                 printf("\n%d records were saved.\n", crypto->lenght);
                break;
        }
            pause();
    }

    fclose(database);
    free(crypto->value);
    free(crypto);

    return 0;
}
