#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // for work with text strings
#include <stdbool.h> // for work with type of bool and constants true and false
// #include <ctype.h>   // isalpha, isspace, islower, isupper, ...
#include <math.h>    // functions from math library
// #include <float.h>   // constants for racional types DBL_MAX, DBL_DIG, ...
// #include <limits.h>  // constants for integer types INT_MAX, INT_MIN, ...
#include <time.h>    // function time and other for work with time
#include <errno.h>

/**
1. načtení dat ze souboru do pole struktur 
(soubor je vyplněný aspoň 11 položkami, každá položka má 4 vlastnosti a jedna z toho je číselná), 
zápis dat z pole struktur do souboru (dvě funkce). Při načítání do pole kontrolujte, 
zda nepřesáhnete velikost pole. Pokud přesáhnete, další položky z pole nenačítejte a vypište hlášku, 
že pole nemá dostatečnou kapacitu.

2. další funkce pro řazení pole aspoň podle dvou vlastností (jedna číselná, jedna textová) - výpis na obrazovku.
    - razeni podle roku zalozeni neni na obrazovce protoze dava vetsi smysl mit podle toho serazenou databazi

3. Zkontrolujte, že vám ostatní funkce pracují bez chyby. 
Měla by tam být funkce pro souhrn (počet, min, max, sum) a jednoduchý filtr.

**/


typedef struct _cryptocurrency {
    int foundation_year;
    char name[41];
    char founder_name[41];
    float price;
} TCryptocurrency;

typedef struct _array {
    TCryptocurrency *value;
    int lenght;
} TArrayOfCrypto;

#define BLOCK 32
#define MAXN 100




/*************** PAUSE AND CLEAR ***************/

void pause(void)
{
    #if defined __WIN32 || defined __WIN64
        system("pause"); 
	#else 
		system("read a");
	#endif
}

void clear(void)
{
	#ifdef _WIN32 
		system("cls");
	#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
	    system("clear");
	//add some other OSes here if needed
	#else
		#error "OS not supported."
	#endif
}



/*************** LOADING AND WRITING OUT ***************/

TArrayOfCrypto * loadCryptocurrencies(FILE *file)
{
    TArrayOfCrypto * array = malloc(sizeof(TArrayOfCrypto));
    if (array == NULL) return NULL;

    array->value = NULL;
    array->lenght = 0;
    int i = 0;

    TCryptocurrency cryptocurrency;

    while(i < MAXN && 
            fscanf(file, "%d %40s %40s %f\n",
                &cryptocurrency.foundation_year,
                cryptocurrency.name,
                cryptocurrency.founder_name,
                &cryptocurrency.price) == 4) {
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

    array->value = realloc(array->value, i * sizeof(TCryptocurrency));
    array->lenght = i;
    return array;
}

void writeCryptocurrencies(FILE *output, TArrayOfCrypto * crypto)
{
    for (int i = 0; i < crypto->lenght; i++) {
            fprintf(output, "%d %s %s %.2f\n",
                crypto->value[i].foundation_year,
                crypto->value[i].name,
                crypto->value[i].founder_name,
                crypto->value[i].price);
    }
}



/*************** SORTING FUNCTIONS - BY YEAR AND LENGTH OF NAME ***************/

// function to swap elements
void swap(TCryptocurrency array[], int x, int y)
{
	TCryptocurrency temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

// function to find the partition position
static inline
int partition(TCryptocurrency array[], int start, int end)
{
	int p = (start + end)/2; // or other selection
	TCryptocurrency pivot = array[p];
	swap(array, p, start); // pivot removal on site

	int left = start;
	int right = end + 1;

	while (true) {
		while (array[++left].foundation_year < pivot.foundation_year) {
			if (left == end) break; // find element >= pivot
		}
		while (pivot.foundation_year < array[--right].foundation_year) {
			// this line doesn't have to be here - it shouldn't be executed in any time
			/* if (left == end) break; // find element >= pivot */ 
		}

		if (left >= right) break;

		swap(array,left, right);
	} // while
	
	swap(array, right, start); // inserting pivot on final position
	return right;
}

void quickSort(TCryptocurrency array[], int start, int end)
{
	if (start >= end) return;

	int pivot_position = partition(array, start, end);

	quickSort(array, start, pivot_position - 1);
	quickSort(array, pivot_position + 1, end);
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

void sortByFoundationYear(FILE *output, TArrayOfCrypto *crypto)
{
    quickSort(crypto->value, 0, crypto->lenght - 1);
    rewind(output);
    writeCryptocurrencies(output, crypto);
    writeCryptocurrencies(stdout, crypto);
    printf("\n\n[DATABASE SORTED BY A FOUNDATION YEAR]: %s\n", isSortedByFoundationYear(crypto) ? "YES" : "NO");
}


static inline
int partitionString(TCryptocurrency array[], int start, int end)
{
	int p = (start + end)/2; // or other selection
	TCryptocurrency pivot = array[p];
	swap(array, p, start); // pivot removal on site

	int left = start;
	int right = end + 1;

	while (true) {
		while (strlen(array[++left].founder_name) < strlen(pivot.founder_name)) {
			if (left == end) break; // find element >= pivot
		}
		while (strlen(pivot.founder_name) < strlen(array[--right].founder_name)) {
			// this line doesn't have to be here - it shouldn't be executed in any time
			/* if (left == end) break; // find element >= pivot */ 
		}

		if (left >= right) break;

		swap(array,left, right);
	} // while
	
	swap(array, right, start); // inserting pivot on final position
	return right;
}

void quickSortString(TCryptocurrency array[], int start, int end)
{
	if (start >= end) return;

	int pivot_position = partitionString(array, start, end);

	quickSortString(array, start, pivot_position - 1);
	quickSortString(array, pivot_position + 1, end);
}


bool isSortedByFounderNameLength(TArrayOfCrypto *crypto)
{
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (strlen(crypto->value[i].founder_name) > strlen(crypto->value[i + 1].founder_name)) {
            return false;
        }
    }
    return true;
}

void sortByFounderNameLength(FILE *output, TArrayOfCrypto *crypto)
{
    quickSortString(crypto->value, 0, crypto->lenght - 1);
    writeCryptocurrencies(output, crypto);
    printf("\n\n[DATABASE SORTED BY THE FOUNDER NAME'S LENGTH]: %s\n", isSortedByFounderNameLength(crypto) ? "YES" : "NO");
}



/*************** SUMMARY ***************/

int averageFoundationYear(TArrayOfCrypto *crypto)
{
    int sum = 0;
    for (int i = 0; i < crypto->lenght - 1; i++) {
        sum += crypto->value[i].foundation_year;
    }

    return sum/(crypto->lenght - 1);
}

void summary(TArrayOfCrypto *crypto)
{
    int average = averageFoundationYear(crypto);
    int youngest = crypto->value[0].foundation_year;
    int oldest = crypto->value[crypto->lenght - 1].foundation_year;
    printf("[SUMMARY]:\n"
           "The number of records: %d\n"
           "The average year of foundation: %d\n"
           "The youngest cryptocurrency was founded in year: %d\n"
           "The oldest cryptocurrency was founded in year: %d\n"
           , crypto->lenght, average, youngest, oldest);
}



/*************** FILTER FUNCTION ***************/

void theOGs(FILE *output, TArrayOfCrypto *crypto)
{
    printf("[THE OG CRYPTOCURRENCIES WHICH WERE FOUNDED BEFORE YEAR 2014]:\n");
    for (int i = 0; i < crypto->lenght - 1; i++) {
        if (crypto->value[i].foundation_year < 2014) {
            fprintf(output, " %s\n", crypto->value[i].name);
        }
    }
}



/*************** MENUs ***************/

void mainMenu()
{
    clear();
	printf(
        "Cryptocurrency Database Program:\n"
        "\t0 - exit\n"
        "\t1 - write out a whole database\n"
        /* "\t2 - add a record\n" */
        /* "\t3 - remove a record\n" */
        /* "\t4 - change a record\n" */
        "\t5 - summary\n"
        "\t6 - sort by a foundation year\n"
        "\t7 - sort by a founder name's length\n"
        "\t8 - see the OGs (which were founded before year 2014)\n"
        "Choose an operation: "
	);

}



/*************** MAIN ***************/

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("ERROR: Program should be executed like this:\n"
               "\tclang main.c;./a.out inputfile\n");
        return -1;
    }

    char *inputpath = argv[1];
    FILE *database = fopen(inputpath, "r+");
    if (database == NULL) return -1;

    TArrayOfCrypto * crypto = loadCryptocurrencies(database);
    if (crypto == NULL) return -2;


    int choice = 1;

    while (choice != 0) {
        mainMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: clear();
                writeCryptocurrencies(stdout, crypto);
                break;
            /* case 2: clear(); */
            /*     break; */
            /* case 3: clear(); */
            /*     break; */
            /* case 4: clear(); */
            /*     break; */
            case 5: clear();
                summary(crypto);
                break;
            case 6: clear();
                sortByFoundationYear(database, crypto);
                break;
            case 7: clear();
                sortByFounderNameLength(stdout, crypto);
                break;
            case 8: clear();
                    theOGs(stdout, crypto);
                break;
        }
        
        if (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8) {
            printf("\n[ERROR]: Uknown operation\n"
                   " Exiting the program...\n"
                    );
            exit(-1);
        }

        if (choice != 0) {
            pause();
        }
    }

    fclose(database);
    free(crypto->value);
    free(crypto);

    return 0;
}
