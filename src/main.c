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

int load(FILE *input, TCryptocurrency a[], int max_length)
{
    int i = 0;
    while (i < max_length && 
        fscanf(input, "%d %40s %40s %f",
            &a[i].foundation_year,
            a[i].name,
            a[i].founder_name,
            &a[i].price) == 4)
    {
        a[i].removed = false;
        i++;
    }

    return i;
}

void write(FILE *output, TCryptocurrency a[], int length)
{
    for (int i = 0; i < length; i++) {
        if (!a[i].removed) {
            fprintf(output, "%d %s %s %f\n",
                a[i].foundation_year,
                a[i].name,
                a[i].founder_name,
                a[i].price);
        }
    }
}

// In progress
/* void sortByFoundationYear(FILE *output, TCryptocurrency a[], int length) */
/* { */
/*     for (int i = 0; i < length; i++) { */
        
/*     } */
    

/* } */

void mainMenu()
{
	printf(
        "Searching Algorithms:\n"
        "0 - exit\n"
        "1 - write out a whole database\n"
        "2 - add record\n"
        "3 - remove record\n"
        "4 - change record\n"
        "5 - summary\n"
        "Choose operation: "
	);

}


int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("ERROR: Program should be executed like this:\n"
               "\tclang main.c;./a.out inputfile\n");
        return -1;
    }

    TCryptocurrency array[MAX];
    char *inputpath = argv[1];

    FILE *database = fopen(inputpath, "r");

    if (database == NULL) return -1;

    int n = load(database, array, MAX);

    write(stdout, array, n);

    
    fclose(database);

    return 0;
}
