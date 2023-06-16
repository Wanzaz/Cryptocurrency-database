#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

void pause(void)
{
    #if defined __WIN32 || defined __WIN64
        system("pause"); 
	#else 
		system("read a");
	#endif
}

/*
 * Clear terminal screen depending on current OS
 * */
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

int checkingForUserChoice()
{
    int choice, check;
    if ((check = scanf("%i", &choice) != 1) || choice < 0 || choice > 13) {
        printf("\n[ERROR]: Uknown operation\n"
               " Exiting the program...\n");
        exit(-4);
        return -4;
    }
    return choice;
}

void clearBuffer(void)
{
    fflush(stdin);
}

void mainMenu()
{
    clear();
	printf(
        "Cryptocurrency Database Program:\n"
        "\t0 - exit\n"
        "\t1 - write out a whole database\n"
        "\t2 - add a record\n"
        "\t3 - change a record\n"
        "\t4 - remove a record\n"
        "\t5 - search data by a cryptocurrency name\n"
        "\t6 - sort by a foundation year\n"
        "\t7 - sort by a cryptocurrency name\n"
        "\t8 - sort by a founder\n"
        /* "\t9 - sort by a price\n" */
        "\t10 - sort by id\n"
        "\t11 - filter data by a foundation year\n"
        "\t12 - summary\n"
        "\t13 - data backup\n"
        "Choose an operation: "
	);
}

void exitProgram()
{
    printf("[INFO]: The program was terminated by the user\n");
    exit(0);
}

