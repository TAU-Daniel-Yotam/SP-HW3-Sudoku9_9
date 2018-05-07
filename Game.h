

#ifndef Game_h
#define Game_h

#include <stdio.h>

#endif /* Game_h */

/*Cell struct*/
typedef struct Cell{
    int value;
    int isFixed;
    int isPlayerMove;
} Cell;

typedef struct Game{
    int blockWidth;
    int blockHeight;
    Cell* board;
    int* solution;
    int isSolveable;
} Game;

int getGameInitParams();
Cell* createEmptyBoard(int x, int y);
int printBoard(Cell* board, int size);
int generatePuzzle(Cell* board, int size);

