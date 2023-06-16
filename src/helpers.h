#ifndef HELPERS_H_
#define HELPERS_H_

#include <stdio.h>

void pause(void);

/*
 * Clear terminal screen depending on current OS
 * */
void clear(void);

int checkingForUserChoice();

void clearBuffer();

void mainMenu();

void exitProgram();

#endif
