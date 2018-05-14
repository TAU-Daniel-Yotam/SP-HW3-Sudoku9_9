#ifndef parser_h
#define parser_h

#include "Game.h"
#include "MainAux.h"
#include <stdio.h>



int getInput(char* command, int size);
int parseCommand(char*command, int* parsedCommand);
int parseSize(char * word);
int parseInt(char* str, int size);

#endif