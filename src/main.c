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


typedef struct {
    int id;
    char name[41];
    char founder_name[41];
    int price;
    int foundation_year;
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
    while(i < max_length && 
            fscanf(input, "%d %40s %40s %d %d",
                &a[i].id,
                a[i].name,
                a[i].founder_name,
                &a[i].price,
                &a[i].foundation_year) == 5)
    {
        a[i].removed = false;
        i++;
    }

    return i;
}



int main(int argc, char *argv[])
{
    TCryptocurrency array[MAX];

    FILE *database = fopen("cryptocurrencies.txt", "r");

    int n = load(database, array, MAX);

    
    fclose(database);

    return 0;
}
