#ifndef mainaux_h
#define mainaux_h

#include "Game.h"
#include <stdio.h>

/**
 * MainAux Summary:
 * This module contains Auxiliary functions to support general actions in the game
 *
 * printBoard   - prints the game board. currently only supports 9x9 sudoku.
 * dealloc      - Deallocs the fields of 'game' that where allocated along the program.
 * printArray   - prints a given int array - used for debugging
 * initArray    - sets all values of a given int array to a given value
 */


/**
 *
 * @param game - a pointer to the game structure
 * @return: void
 */
void printBoard(Game* game);


/**
 * @param game - a pointer to the game structure
 * @return 0 (always)
 */
int dealloc(Game* game);

/**
 *
 * @param a - an int array
 * @param size - the size of the array
 * @param v - a value to search
 * @return 1 if v is in a, or 0 o.w
 */
int inArray(int a[],int size,int v);

/**
 *
 * @param a  - an int array
 * @param size - the size of the array
 */
void printArray(void*a,int size);

/**
 *
 * @param a  - an int array
 * @param size - the size of the array
 * @param initValue - the value to set all values of 'a' to
 * @return
 */
int initArray(int*a, int size, int initValue);
#endif
