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

typedef struct
{
    char name[41];
    char founder_name[41];
    int price;
    int foundation_year;
} TCryptocurrency;


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





int main(int argc, char *argv[])
{

    

    return 0;
}
