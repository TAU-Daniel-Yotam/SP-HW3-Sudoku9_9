

#ifndef Game_h
#define Game_h

#include <stdio.h>

#endif /* Game_h */

/*Cell struct*/
typedef struct Cell{
    int value;
    int isConst;
} Cell;

int getGameInitParams();
Cell* createEmptyBoard(int x, int y);
int printBoard(Cell* board, int size);
int generatePuzzle(Cell* board, int size);

