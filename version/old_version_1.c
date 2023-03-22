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


typedef struct {
    int foundation_year;
    char name[41];
    char founder_name[41];
    float price;
    bool removed;
} TCryptocurrency;

#define MAX 100




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

int load(FILE *input, TCryptocurrency a[], int max_length)
{
    int i = 0;
    while (i < max_length && 
        fscanf(input, "%d %40s %40s %f\n",
            &a[i].foundation_year,
            a[i].name,
            a[i].founder_name,
            &a[i].price) == 4)
    {
        a[i].removed = false;
        i++;
    }

    /* rewind(input); */
    return i;
}

void write(FILE *output, TCryptocurrency a[], int length)
{
    for (int i = 0; i < length; i++) {
        if (!a[i].removed) {
            fprintf(output, "%d %s %s %.2f\n",
                a[i].foundation_year,
                a[i].name,
                a[i].founder_name,
                a[i].price);
        }
    }
}

void writeOutOfWholeDatabase(FILE *output, TCryptocurrency a[], int length)
{
    for (int i = 0; i < length; i++) {
        if (!a[i].removed) {
            fprintf(output, "%d %s %s %.2f\n",
                a[i].foundation_year,
                a[i].name,
                a[i].founder_name,
                a[i].price);
        }
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

void _quickSort(TCryptocurrency array[], int start, int end)
{
	if (start >= end) return;

	int pivot_position = partition(array, start, end);

	_quickSort(array, start, pivot_position - 1);
	_quickSort(array, pivot_position + 1, end);
}

void quickSort(TCryptocurrency array[], int n)
{
	_quickSort(array, 0, n - 1);
	
}

bool isSortedByFoundationYear(TCryptocurrency array[], int length)
{
    for (int i = 0; i < length - 1; i++) {
        if (array[i].foundation_year > array[i + 1].foundation_year) {
            return false;
        }
    }
    return true;
}

void sortByFoundationYear(FILE *output, TCryptocurrency array[], int length)
{
    quickSort(array, length);
    rewind(output);
    write(output, array, length);
    write(stdout, array, length);
    printf("\n\n[DATABASE SORTED BY A FOUNDATION YEAR]: %s\n", isSortedByFoundationYear(array, length) ? "YES" : "NO");
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

void _quickSortString(TCryptocurrency array[], int start, int end)
{
	if (start >= end) return;

	int pivot_position = partitionString(array, start, end);

	_quickSortString(array, start, pivot_position - 1);
	_quickSortString(array, pivot_position + 1, end);
}

void quickSortString(TCryptocurrency array[], int n)
{
	_quickSortString(array, 0, n - 1);
	
}

bool isSortedByFounderNameLength(TCryptocurrency array[], int length)
{
    for (int i = 0; i < length - 1; i++) {
        if (strlen(array[i].founder_name) > strlen(array[i + 1].founder_name)) {
            return false;
        }
    }
    return true;
}

void sortByFounderNameLength(FILE *output, TCryptocurrency array[], int length)
{
    quickSortString(array, length);
    write(output, array, length);
    printf("\n\n[DATABASE SORTED BY THE FOUNDER NAME'S LENGTH]: %s\n", isSortedByFounderNameLength(array, length) ? "YES" : "NO");
}



/*************** SUMMARY ***************/

int averageFoundationYear(TCryptocurrency array[], int n)
{
    int sum = 0;
    for (int i = 0; i < n - 1; i++) {
        sum += array[i].foundation_year;
    }

    return sum/(n - 1);
}

void summary(TCryptocurrency array[], int n)
{
    int average = averageFoundationYear(array, n);
    int youngest = array[0].foundation_year;
    int oldest = array[n - 1].foundation_year;
    printf("[SUMMARY]:\n"
           "The number of records: %d\n"
           "The average year of foundation: %d\n"
           "The youngest cryptocurrency was founded in year: %d\n"
           "The oldest cryptocurrency was founded in year: %d\n"
           , n, average, youngest, oldest);
}



/*************** FILTER FUNCTION ***************/

void theOGs(FILE *output, TCryptocurrency array[], int n)
{
    printf("[THE OG CRYPTOCURRENCIES WHICH WERE FOUNDED BEFORE YEAR 2014]:\n");
    for (int i = 0; i < n - 1; i++) {
        if (array[i].foundation_year < 2014) {
            fprintf(output, " %s\n", array[i].name);
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

    TCryptocurrency array[MAX];
    char *inputpath = argv[1];

    FILE *database = fopen(inputpath, "r+");

    if (database == NULL) return -1;

    int n = load(database, array, MAX);


    int choice = 1;

    while (choice != 0) {
        mainMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: clear();
                writeOutOfWholeDatabase(stdout, array, n);
                break;
            /* case 2: clear(); */
            /*     break; */
            /* case 3: clear(); */
            /*     break; */
            /* case 4: clear(); */
            /*     break; */
            case 5: clear();
                summary(array, n);
                break;
            case 6: clear();
                sortByFoundationYear(database, array, n);
                break;
            case 7: clear();
                sortByFounderNameLength(stdout, array, n);
                break;
            case 8: clear();
                    theOGs(stdout, array, n);
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

    return 0;
}
