#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "actions.h"
#include "helpers.h"
#include "lists.h"
#include "comparing.h"


int loadOneCrypto(FILE *input, TCryptocurrency *cryptocurrency)
{
    int temp;
    if (fscanf(input, "%d %d %40s %40s %f %d\n", 
        &cryptocurrency->id,
        &cryptocurrency->foundation_year,
        cryptocurrency->name,
        cryptocurrency->founder_name,
        &cryptocurrency->price,
        &temp) == 6) {

        cryptocurrency->deleted = temp;

        return 0;
    }
    return -5;
}


TArrayOfCrypto * loadCryptocurrencies(FILE *file)
{
    TArrayOfCrypto * array = malloc(sizeof(TArrayOfCrypto));
    array->capacity = sizeof(TArrayOfCrypto);
    if (array == NULL) return NULL;

    array->value = NULL;
    array->lenght = 0;
    int i = 0;


    TCryptocurrency cryptocurrency;

    int checking;

    while(i < MAXN && 
            (checking = loadOneCrypto(file, &cryptocurrency)) == 0) {
        if (i == array->lenght) {
            array->lenght += BLOCK;
            TCryptocurrency * temp = realloc(array->value, array->lenght * sizeof(TCryptocurrency));
            if (temp == NULL) {
                return array;
            }
            array->value = temp;
        }
        array->value[i++] = cryptocurrency;
    }

    if (checking < 6 && checking >= 0) {
        printf("[SYNTAX ERROR]: while loading data from a database\n"
               "\tCorrect the format of the data\n");
        exit(-3);
    }

    array->value = realloc(array->value, i * sizeof(TCryptocurrency));
    array->lenght = i;
    return array;
}

void printOneCrypto(FILE *file, TCryptocurrency cryptocurrency)
{
    if (!cryptocurrency.deleted) {
        fprintf(file, "%d %d %s %s %.2f\n", 
        cryptocurrency.id,
        cryptocurrency.foundation_year,
        cryptocurrency.name,
        cryptocurrency.founder_name,
        cryptocurrency.price);
    }
}

void writeCryptocurrencies(FILE *output, TArrayOfCrypto *crypto)
{
    rewind(output);
    for (int i = 0; i < crypto->lenght; i++) {
        printOneCrypto(output, crypto->value[i]);
    }
}

// function to swap elements
void swap(TCryptocurrency array[], int x, int y)
{
	TCryptocurrency temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

// function to find the partition position
static inline
int partition(TCryptocurrency array[], int start, int end, CompareType type)
{
	int p = (start + end)/2; // or other selection
	TCryptocurrency pivot = array[p];
	swap(array, p, start); // pivot removal on site

	int left = start;
	int right = end + 1;

	while (true) {
		while (compare(array[++left], pivot, type) < 0) {
			if (left == end) break; // find element >= pivot
		}
		while (compare(pivot, array[--right], type) < 0) {
			// this line doesn't have to be here - it shouldn't be executed in any time
			/* if (left == end) break; // find element >= pivot */ 
		}

		if (left >= right) break;

		swap(array,left, right);
	} // while
	
	swap(array, right, start); // inserting pivot on final position
	return right;
}

void quickSort(TCryptocurrency array[], int start, int end, CompareType type)
{
	if (start >= end) return;

	int pivot_position = partition(array, start, end, type);

	quickSort(array, start, pivot_position - 1, type);
	quickSort(array, pivot_position + 1, end, type);
}

bool isSortedByFoundationYear(TArrayOfCrypto *crypto)
{
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (crypto->value[i].foundation_year > crypto->value[i + 1].foundation_year) {
            return false;
        }
    }
    return true;
}

void sort(FILE *output, TArrayOfCrypto *crypto, CompareType type)
{
    quickSort(crypto->value, 0, crypto->lenght - 1, type);
    rewind(output);
    writeCryptocurrencies(output, crypto);
}

