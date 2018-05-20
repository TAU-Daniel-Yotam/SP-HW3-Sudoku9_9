#ifndef parser_h
#define parser_h

#include "Game.h"
#include "MainAux.h"
#include <stdio.h>


/**
 *
 * @param command
 * @param size
 * @return
 */
int getInput(char* command, int size);

/**
 *
 * @param command
 * @param parsedCommand
 * @return
 */
int parseCommand(char*command, int* parsedCommand);

/**
 *
 * @param word
 * @return
 */
int parseSize(char * word);

/**
 *
 * @param str
 * @param size
 * @return
 */
int parseInt(char* str, int size);

#endif