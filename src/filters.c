#include <stdio.h>
#include "types.h"
#include "helpers.h"
#include "lists.h"


// TODO: My attempt to make a filter function more generic
/* void mapNotDeletedCrypto(TCryptocurrency *cryptocurrency, void (*function)(TCryptocurrency *crypto)) */
/* { */
/*         if (!cryptocurrency) { */
/*             function(cryptocurrency); */
/*         } */
/* } */


int numberOfNotDeletedCrypto(TArrayOfCrypto *crypto)
{
    int not_deleted = 0;
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (!crypto->value[i].deleted) {
            not_deleted++;
        }
    }

    return not_deleted;
}

int averageFoundationYear(TArrayOfCrypto *crypto)
{
    int sum = 0;
    int not_deleted = 0;
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (!crypto->value[i].deleted) {
            sum += crypto->value[i].foundation_year;
            not_deleted++;
        }
    }

    return sum/not_deleted;
}

int oldest(TArrayOfCrypto *crypto)
{
    int oldest = crypto->value[0].foundation_year;
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (!crypto->value[i].deleted && crypto->value[i].foundation_year < oldest) {
            oldest = crypto->value[i].foundation_year;
        }
    }

    return oldest;
}

int youngest(TArrayOfCrypto *crypto)
{
    int youngest = crypto->value[0].foundation_year;
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (!crypto->value[i].deleted && crypto->value[i].foundation_year > youngest) {
            youngest = crypto->value[i].foundation_year;
        }
    }

    return youngest;
}


void summary(TArrayOfCrypto *crypto)
{
    printf("[SUMMARY]:\n"
           "The number of records: %d\n"
           "The average year of foundation: %d\n"
           "The youngest cryptocurrency was founded in year: %d\n"
           "The oldest cryptocurrency was founded in year: %d\n"
           , numberOfNotDeletedCrypto(crypto), averageFoundationYear(crypto), youngest(crypto), oldest(crypto));
}



/*************** FILTER FUNCTION ***************/

void foundedBeforeYear(TArrayOfCrypto *crypto)
{
    int before_year;
    printf("[INSTRUCTION]: By which year do you wanna see the founded cryptocurrencies: \n");
    scanf("%i", &before_year);
    clear();
    printf("[THE CRYPTOCURRENCIES WHICH WERE FOUNDED BEFORE YEAR %i]:\n", before_year);
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (crypto->value[i].foundation_year < before_year && (!crypto->value[i].deleted)) {
            writeOne(stdout, crypto->value[i], DATA_FORMAT);
        }
    }
}
