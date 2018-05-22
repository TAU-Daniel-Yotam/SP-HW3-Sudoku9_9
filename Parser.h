#ifndef parser_h
#define parser_h

#include "Game.h"
#include "MainAux.h"
#include <stdio.h>

/**
* Parser Summary:
* This module contains all the function related to receiving and interpreting the input from the user
*
* getInput      - receives input from the user.
* parsedCommand - Interprets the command that the user wants to invoke.
* parseSize     - calculates the size of the received command.
* parseInt      - Converts a string to a number in base 10
*/


/**
* @param command- a pointer to a string that will contain the input from the user.
* @param size- the size of the string.

* @return 0 if the input not received else 1.
*/
int getInput(char* command, int size);


/**
* @param word- a poiner to string that contain user input.
* @param parsedCommand- an int array :
         parsedCommand[0]- 1=set,2=hint,3=validate,4=restart,5=exit,6=white spaces only in input, -1=invalid command.
		 parsedCommand[1]-the column of the cell
		 parsedCommand[2]=the row of the cell.
		 parsedCommand[3]=the value
* @return parsedCommand[0]
*/
int parseCommand(char*command, int* parsedCommand);

/**
* @param word - a pointer to the input from the user.
* @return the size of the input .
*/

int parseSize(char * word);

/**
* @param word - a string that represents a number.
* @return the the number as an integer.
*/
int parseInt(char* str, int size);

#endif

