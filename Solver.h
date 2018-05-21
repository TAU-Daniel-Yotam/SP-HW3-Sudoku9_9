/**
 * Solver.h summary:
 * This module contains all functions that are related to the backtrack algorithm to solve sudoku puzzles
 *
 * Functions:
 * randomSolve      - randomly solves an empty sudoku board as a part of generating a new puzzle
 * randSolveRec     - used by randomSolve, this function implements a recursive version of the randomized backtrack algorithm
 * detSolve         - solves a given sudoku puzzle deterministically if possible, or announces that the puzzle is unsolvable
 * detSolveRec      - used by detSolve, this function implements a recursive version of the deterministic backtrack algorithm
 * findRightMove    - finds the first legal value to put in a cell starting from a given value
 */

#ifndef solver_h
#define solver_h

#include "Game.h"
#include "MainAux.h"
#include <stdio.h>

/**
 *
 * @param game - a pointer to the current Game instance
 * @return 1 if a solution was found, or 0 if board is unsolvable
 */
int detSolve(Game* game);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param solution - a copy of the board that the function will solve the puzzle with. If a solution is found
 *                   the function will replace the game's solution with this copy
 * @param start - an index to start the backtracking algorithm from
 * @param index - an index to the current location of the algorithm on the board
 * @param moveDir - 1 if the algorithm is moving forward, or (-1) if moving backward
 * @return 1 if a solution was found, or 0 if board is unsolvable
 */
int detSolveRec(Game* game, int*solution, int start, int index, int moveDir);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param solution - a copy of the board that the function will solve the puzzle with. If a solution is found
 *                   the function will replace the game's solution with this copy
 * @param x - the column of the cell
 * @param y - the row of the cell
 * @param from - a starting value represents the range of possible values to this cell - [from,9]
 * @return i in range [from,9], i = min_i(checkLegal(game,x,y,i))
 */
int findRightMove(Game* game,int * solution , int x, int y, int from);

/**
 *
 * @param game - a pointer to the current Game instance
 * @return 1 if game if puzzle is solved, 0 if puzzle isn't solved, -1 if memory allocation error occurred
 */
int randomSolve(Game* game);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param solution - a copy of game->solution
 * @param start - the index to start solving from
 * @param index - the current index to push a value to
 * @param options - 2d array that remembers for each cell the values that were already tried to be pushed into it
 * @return 1 if game if puzzle is solved, 0 if puzzle isn't solved, -1 if memory allocation error occurred
 */
int randSolveRec(Game* game, int* solution, int start, int index, int**options);

#endif
