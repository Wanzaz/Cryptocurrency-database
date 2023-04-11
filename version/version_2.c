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

FINALNI ZADANI
Do cvičení si přineste projekt. 
Pokud pracujete  se seznamem dat doplňte si vyhledávání podle určité položky (aspoň jedné). 
Také doplňte mazání položky.  Mazání může být fyzické nebo logické (příznak smazáno) 
a je právě vázáno na vyhledávání položky. 
Z minulého roku by mělo fungovat přidání položky a úprava položky.
Projekt by měl být už ve finální verzi.

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

    int checking;

    while(i < MAXN && 
            (checking = fscanf(file, "%d %40s %40s %f\n",
                &cryptocurrency.foundation_year,
                cryptocurrency.name,
                cryptocurrency.founder_name,
                &cryptocurrency.price)) == 4) {
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

    if (checking < 4 && checking >= 0) {
        printf("[SYNTAX ERROR]: while loading data from a database\n"
               "\tCorrect the format of the data\n");
        exit(-3);
    }

    array->value = realloc(array->value, i * sizeof(TCryptocurrency));
    array->lenght = i;
    return array;
}

void writeCryptocurrencies(FILE *output, TArrayOfCrypto *crypto)
{
    rewind(output);
    for (int i = 0; i < crypto->lenght; i++) {
            fprintf(output, "%d %s %s %.2f\n",
                crypto->value[i].foundation_year,
                crypto->value[i].name,
                crypto->value[i].founder_name,
                crypto->value[i].price);
    }
}



/*************** SORTING FUNCTIONS - BY YEAR AND NAME ***************/

typedef enum _CompareType
{
    ByFoundationYear = 1,
    ByName = 0, // alphabetically
} CompareType;

int compare(TCryptocurrency x, TCryptocurrency y, CompareType type)
{
    switch (type) {
        case ByFoundationYear:
            return x.foundation_year - y.foundation_year;
        case ByName:
            return strcmp(x.name, y.name);
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



/*************** SUMMARY ***************/

int averageFoundationYear(TArrayOfCrypto *crypto)
{
    int sum = 0;
    for (int i = 0; i < crypto->lenght - 1; i++) {
        sum += crypto->value[i].foundation_year;
    }

    return sum/(crypto->lenght - 1);
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
        if (crypto->value[i].foundation_year < before_year) {
            fprintf(output, "%d %s %s %.2f\n",
                crypto->value[i].foundation_year,
                crypto->value[i].name,
                crypto->value[i].founder_name,
                crypto->value[i].price);
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



/*************** SEARCHING ***************/

void searchByName(TArrayOfCrypto *crypto)
{
    int i = 0;
    int found = 0;
    char searched_name[41];
    printf("[INSTRUCTION]: Enter a name of searched cryptocurrency: \n");
    scanf("%40s", searched_name);

    for (int i = 0; i < crypto->lenght; i++) {
        if (strcmp(crypto->value[i].name, searched_name) == 0) {
            printf("%d %s %s %.2f\n",
                crypto->value[i].foundation_year,
                crypto->value[i].name,
                crypto->value[i].founder_name,
                crypto->value[i].price);
            found++;
        }
    }

    if (found == 0) {
        printf("[ERROR]: Item wasn't found.\n");
    }
}



/*************** BACKUP ***************/

void dataBackup(FILE *output, TArrayOfCrypto *crypto)
{
    printf("[INFO]: Data were successfully backed up.\n");
    writeCryptocurrencies(output, crypto);
}



/*************** ADD, CHANGE, REMOVE RECORD  ***************/

void addRecord(FILE *output, TArrayOfCrypto *crypto)
{
    TCryptocurrency new_cryptocurrency;
    printf("[INSTRUCTION]: Enter info in format: foundation_year name founder_name price\n");
    if (scanf("%d %40s %40s %f", 
                &new_cryptocurrency.foundation_year,
                new_cryptocurrency.name,
                new_cryptocurrency.founder_name,
                &new_cryptocurrency.price) == 4) {

        crypto->value[crypto->lenght] = new_cryptocurrency;
        crypto->lenght++;

        printf("[INFO]: Record was successfully added.\n\n\n");
        writeCryptocurrencies(output, crypto);
        
    } else {
        printf("[ERROR]: Information in a wrong format.\n");
    }
}

void changeRecord(FILE *output, TArrayOfCrypto *crypto)
{
    int index;
    writeCryptocurrencies(stdout, crypto);

    printf("\n\n[INSTRUCTION]: Enter record index which you wanna change: \n");
    scanf("%d", &index);

    if (index >= 0 && index < crypto->lenght) {
        TCryptocurrency new_cryptocurrency;
        printf("[INSTRUCTION]: Enter info in format: foundation_year name founder_name price\n");

        if (scanf("%d %40s %40s %f", 
                    &new_cryptocurrency.foundation_year,
                    new_cryptocurrency.name,
                    new_cryptocurrency.founder_name,
                    &new_cryptocurrency.price) == 4) {

            crypto->value[index] = new_cryptocurrency;

        } else {
            printf("[ERROR]: Information in a wrong format.\n");
        }

    } else {
        printf("[ERROR]: Wrong index.\n");
    }
    printf("[INFO]: Record was successfully changed.\n\n\n");
    writeCryptocurrencies(output, crypto);
}

void removeRecord(FILE *output, TArrayOfCrypto *crypto)
{
    int index;
    writeCryptocurrencies(stdout, crypto);

    printf("\n\n[INSTRUCTION]: Enter record index which you wanna delete: \n");
    scanf("%d", &index);

    if (index >= 0 && index < crypto->lenght) {
        for (int i = index; i < crypto->lenght - 1; i++) {
            crypto->value[i] = crypto->value[i + 1];
        }

        crypto->lenght--;
        printf("[INFO]: Record was successfully deleted.\n\n\n");
        writeCryptocurrencies(output, crypto);
    
    } else {
        printf("[ERROR]: Wrong index.\n");
    }
}



/*************** MENUs ***************/

int checkingForUserChoice()
{
    int choice, check;
    if ((check = scanf("%i", &choice) != 1)) {
        printf("\n[ERROR]: Uknown operation\n"
               " Exiting the program...\n");
        exit(-4);
        return -4;
    }
    return choice;
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
        "\t7 - sort by a cryptocurrency name alphabetically\n"
        "\t8 - filter data by a foundation year\n"
        "\t9 - summary\n"
        "\t10 - data backup\n"
        "Choose an operation: "
	);
}

void exitProgram()
{
    printf("[INFO]: The program was terminated by the user\n");
    exit(-5);
}



/*************** MAIN ***************/
// TODO 
// - enum for error returns
// - lower_case_names 
// - add ID to every item
// - error with wrong format

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("[ERROR]: Program should be executed like this:\n"
               "\t./a.out inputfile\n");
        return -1;
    }

    char *inputpath = argv[1];
    FILE *database = fopen(inputpath, "r+");
    if (database == NULL) return -1;


    // Warning a user if the data were unsuccessfully loaded from the database
    TArrayOfCrypto * crypto = loadCryptocurrencies(database);
    if (crypto == NULL) return -2;

    int choice = 1;
    while (choice != -4) {
        mainMenu();

        int choice = checkingForUserChoice();
        
        switch(choice) {
            case 0: clear();
                exitProgram();
            case 1: clear();
                writeCryptocurrencies(stdout, crypto);
                break;
            case 2: clear();
                addRecord(stdout, crypto);
                break;
            case 3: clear();
                changeRecord(stdout, crypto);
                break;
            case 4: clear();
                removeRecord(stdout, crypto);
                break;
            case 5: clear();
                searchByName(crypto);
                break;
            case 6: clear();
                sort(stdout, crypto, ByFoundationYear);
                break;
            case 7: clear();
                sort(stdout, crypto, ByName); // alphabetically
                break;
            case 8: clear();
                beforeYear(stdout, crypto);
                break;
            case 9: clear();
                summary(crypto);
                break;
            case 10: clear();
                dataBackup(database, crypto);
                printf("%d\n", crypto->lenght);
                break;
        }
            pause();
    }

    fclose(database);
    free(crypto->value);
    free(crypto);

    return 0;
}

