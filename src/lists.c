#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "records.h"
#include "helpers.h"
#include "lists.h"
#include "comparing.h"


int loadOneCrypto(FILE *input, TCryptocurrency *cryptocurrency, char* format)
{
    int temp, result;
    result = fscanf(input, format, 
        &cryptocurrency->id,
        &cryptocurrency->foundation_year,
        cryptocurrency->name,
        cryptocurrency->founder_name,
        &cryptocurrency->price,
        &temp); 

        cryptocurrency->deleted = temp;
    return result;
}

int loadOneCryptoInput(FILE *input, TCryptocurrency *cryptocurrency, char* format)
{
    int result;
    result = fscanf(input, format, 
        &cryptocurrency->foundation_year,
        cryptocurrency->name,
        cryptocurrency->founder_name,
        &cryptocurrency->price); 

    return result;
}


TArrayOfCrypto * loadCryptocurrencies(FILE *file)
{
    TArrayOfCrypto * array = malloc(sizeof(TArrayOfCrypto));
    array->lenght = sizeof(TArrayOfCrypto);
    if (array == NULL) return NULL;

    array->value = NULL;
    array->lenght = 0;
    int i = 0;


    TCryptocurrency cryptocurrency;

    int checking;

    while(i < MAXN && 
            (checking = loadOneCrypto(file, &cryptocurrency, DATA_FORMAT)) == 6) {
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

/** 
 * Outputs list to dedicated file with given format string
 */
void write(FILE* output, TArrayOfCrypto *crypto, char* format)
{
    for (int i = 0; i < crypto->lenght; i++) {
        if (crypto->value[i].deleted) {
            continue;
        }

        writeOne(output, crypto->value[i], format);
    }
}

/** 
 * Outputs list to dedicated file with given format string with deleted records
 */

void writeAll(FILE* output, TArrayOfCrypto *crypto, char* format)
{
    for (int i = 0; i < crypto->lenght; i++) {
        writeOnePrint(output, crypto->value[i], format);
    }
}

/**
 * Outputs head of table
 */
void printHead()
{
    puts(
        "+----+-----------------+---------------+-------------------+-----------+\n"
        "| id | Foundation year |  Crypto name  | Founder name      | Price $   |\n"
        "|----+-----------------+---------------+-------------------+-----------|"
    );
}

void printTail()
{
    puts(
        "+----+-----------------+---------------+-------------------+-----------+\n"
    );
}

/**
 * Prints whole list to stdout with pretty format
 */
int print(TArrayOfCrypto* crypto)
{
    printHead();
    write(stdout, crypto, PRETTY_FORMAT);
    printTail();
    return 0;
}

void writeOne(FILE *file, TCryptocurrency cryptocurrency, char* format)
{
    fprintf(file, format, 
    cryptocurrency.id,
    cryptocurrency.foundation_year,
    cryptocurrency.name,
    cryptocurrency.founder_name,
    cryptocurrency.price);
}

void writeOnePrint(FILE *file, TCryptocurrency cryptocurrency, char* format)
{
    fprintf(file, format, 
    cryptocurrency.id,
    cryptocurrency.foundation_year,
    cryptocurrency.name,
    cryptocurrency.founder_name,
    cryptocurrency.price,
    cryptocurrency.deleted);
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
    print(crypto);
}

