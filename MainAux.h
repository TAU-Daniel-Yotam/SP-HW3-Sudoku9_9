#ifndef mainaux_h
#define mainaux_h

#include "Game.h"
#include <stdio.h>


void printBoard(Game* game);
int dealloc(Game* game);
int inArray(int a[],int size,int v);
void printArray(void*a,int size);
/*int compareArrays(int*a,int sizeA, int*b, int sizeB);*/
#endif
