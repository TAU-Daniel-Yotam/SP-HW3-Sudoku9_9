

#ifndef Solver_h
#define Solver_h
#include "Game.h"
#include <stdio.h>

#endif /* Solver_h */

int randomSolve(Game* game);
int detSolve(Game* game);
int detSolveRec(Game* game, int*solution, int start, int index, int moveDir);
int findRightMove(Game* game,int * solution , int x, int y, int from);
int randSolveRec(Game* game, int* solution, int start, int index, int**options, int moveDir);


