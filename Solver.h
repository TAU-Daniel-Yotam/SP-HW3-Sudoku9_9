

#ifndef Solver_h
#define Solver_h

#include <stdio.h>

#endif /* Solver_h */

int randomSolve(Cell* board, int size, int seed);
int deterministicSolve(Cell* board, int size);
int checkLegal(Game game,int x, int y, int value);

