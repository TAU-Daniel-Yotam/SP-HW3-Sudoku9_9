

#ifndef Solver_h
#define Solver_h
#include "Game.h"
#include <stdio.h>

#endif /* Solver_h */

int randomSolve(Game game);
int deterministicSolve(Cell* board, int size);
int checkLegal(Game game,int x, int y, int value);

