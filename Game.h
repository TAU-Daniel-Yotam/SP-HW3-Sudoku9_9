#include "MainAux.h"
#include "Solver.h"
#include <stdio.h>

#ifndef Game_h
#define Game_h



/*Cell struct*/
typedef struct Cell{
    int value;
    int isFixed;
    int isPlayerMove;
}Cell;

typedef struct Game{
    int blockWidth;
    int blockHeight;
    Cell* board;
    int boardSize;
    int* solution;
}Game;


Game* getGameInitParams(Game* game, Game*newGame, int w, int h);

int set(Game* game, int x, int y, int  value);

int checkBlock(Game* game,int x, int y, int value);

int hint(Game * game, int x, int y);

int validate(Game* game);

int getBoardIndex(Game* game, int x, int y);

int checkLegal(Game* game,int x, int y, int value);

int checkRowColumn(Game *game, int x, int y, int value);

int position(Game* game ,int index,int*a);

int findFirstNotFixed(Game* game);

int exitGame(Game* game);

/*Pre: y,x<=game.blockWidth * blockHeight
 *Post: ret={i|1<=i<=blockWidth * blockHeight && i is a legal value in (x,y)}*/
int *getAllPossibleValues(Game* game,int* solution,int*pastValues, int x,int y,int*values);

int* duplicateSol(Game*game);

int winningBoard(Game* game);

int checkLegalSol(Game* game,int* sol ,int x, int y, int value);

int checkBlockSol(Game* game, int* sol, int x, int y, int value);

int checkRowColumnSol(Game* game, int* sol, int x, int y, int value);

int addHints(Game*game,int hints);

#endif
