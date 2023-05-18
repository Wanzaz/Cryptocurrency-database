#include <stdio.h>
#include "types.h"
#include "helpers.h"
#include "lists.h"


int averageFoundationYear(TArrayOfCrypto *crypto)
{
    int sum = 0;
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (!crypto->value[i].deleted) {
            sum += crypto->value[i].foundation_year;
        }
    }

    return sum/(crypto->lenght - 1);
}

int lenghtOfNotDeletedCrypto(TArrayOfCrypto *crypto)
{
    int length;
    for (int i = 0; i < crypto->lenght - 1; i++) {
        
    }

}

int oldest(TArrayOfCrypto *crypto)
{
    return crypto->value[crypto->lenght - 1].foundation_year;
}

int youngest(TArrayOfCrypto *crypto)
{
    return crypto->value[0].foundation_year;
}

void summary(TArrayOfCrypto *crypto)
{
    printf("[SUMMARY]:\n"
           "The number of records: %d\n"
           "The average year of foundation: %d\n"
           "The youngest cryptocurrency was founded in year: %d\n"
           "The oldest cryptocurrency was founded in year: %d\n"
           , crypto->lenght, averageFoundationYear(crypto), youngest(crypto), oldest(crypto));
}



/*************** FILTER FUNCTION ***************/

void foundedBeforeYear(FILE *output, TArrayOfCrypto *crypto, int before_year)
{
    printf("[THE CRYPTOCURRENCIES WHICH WERE FOUNDED BEFORE YEAR %i]:\n", before_year);
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (crypto->value[i].foundation_year < before_year && (!crypto->value[i].id)) {
            printOneCrypto(output, crypto->value[i]);
        }
    }
}

void beforeYear(FILE *output, TArrayOfCrypto *crypto)
{
    int before_year;
    printf("[INSTRUCTION]: By which year do you wanna see the founded cryptocurrencies: \n");
    scanf("%i", &before_year);
    clear();
    foundedBeforeYear(output, crypto, before_year);
}
