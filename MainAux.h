

#ifndef MainAux_h
#define MainAux_h
#include "Game.h"

#include <stdio.h>

#endif /* MainAux_h */

/*Generate a random int between 1 and an upper bound
 * Post: 1<=ret<=bound*/
int getRandomInt(int bound);
int calcSizeOfArray(int*a);
void printboard(Game game);
int dealloc(Game* game);