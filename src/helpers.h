#ifndef HELPERS_H_
#define HELPERS_H_

#include "types.h"
#include <stdio.h>

void pause(void);

/*
 * Clear terminal screen depending on current OS
 * */
void clear(void);

int checkingForUserChoice();

void mainMenu();

void exitProgram();

#endif
