/**
 * Game summary:
 * This module contains all functions and structs that are related to the "flow" of the game.
 * The Sudoku board is represented as a 1 dimensional array of "Cell"s
 *
 * Structs:
 * struct Cell          - contains the value of the cell in the game
 *                        and binary flags to indicate if a cell is fixed or where filled by the player
 * struct Game          - Saves the current state of the game
 *
 * Functions:
 * getGameInitParams    - Initializes the game by creating a "Game" instance an it's fields.
 * set                  - Handles the "set" command when the user invokes it
 * hint                 - Handles the "hint" command when the user invokes it
 * validate             - Handles the "validate" command when the user invokes it
 * exitGame             - Handles the "exit" command when the user invokes it
 * checkBlock           - Checks if the user's move is legal "blockwise"
 * checkRowColumn       - Checks if the user's move is legal "row and column - wise"
 * checkBlockSol        - Same as CheckBlock but used for generating a puzzle
 * checkRowColumnSol    - Same as checkRowColumn but used for generating a puzzle
 * checkLegal           - Checks if a player's move is legal
 * checkLegalSol        - Same as CheckLegal but used for generating a puzzle
 * getBoardIndex        - Converts x-y coordinates to the equal index in the representing array
 * position             - Converts an index in the representing array to x-y coordinates
 * findFirstNotFixed    - Finds the first not fixed cell in the board
 * getAllPossibleValues - Lists all the numbers that are legal in a certain cell
 * duplicateSol         - Duplicates the solution array so we can freely change it's values without influencing the game
 * winningBoard         - Checks if the current game board is solved
 * addHints             - Randomly adds fixed cells to the board as hints
 *
 */

#include "MainAux.h"
#include "Solver.h"
#include <stdio.h>

#ifndef Game_h
#define Game_h



/**
 *
 */
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

/**
 * @param game - a pointer to the current Game instance (or NULL if it's the first game)
 * @param newGame - a pointer to a new Game instance
 * @param w - the games block width
 * @param h - the games block height
 * @return Game* - a pointer to a new game instance
 */
Game* getGameInitParams(Game* game, Game*newGame, int w, int h);

/**
 * @param game - a pointer to the current Game instance
 * @param x - the column of the cell to be set
 * @param y - the row of the cell to be set
 * @param value - the value to set cell(x,y) to
 * @return 1 if(winningBoard(game)), or 0 o.w
 */
int set(Game* game, int x, int y, int  value);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param x - the column of the cell to be checked
 * @param y - the row of the cell to be checked
 * @param value - the value to check
 * @return 1 the block that contains (x,y) doesnt contain value, or 0 o.w
 */
int checkBlock(Game* game,int x, int y, int value);

/** the function prints the value of the solution in the given coordinates
 *
 * @param game - a pointer to the current Game instance
 * @param x - the column of the cell to give a hint to
 * @param y - the row of the cell to give a hint to
 * @return 0
 */
int hint(Game * game, int x, int y);

/**the function invokes a deterministic solver and prints if the current board is solvable
 *
 * @param game - a pointer to the current Game instance
 * @return 1 if board is solvable, or 0 o.w
 */
int validate(Game* game);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param x - the column of the cell
 * @param y - the row of the cell
 * @return game->blockHeight * game->blockWidth * (y - 1) + (x - 1)
 */
int getBoardIndex(Game* game, int x, int y);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param x - the column of the cell
 * @param y - the row of the cell
 * @param value - the value to be checked if legal in board(x,y)
 * @return 1 if(checkRowColumn(game,x,y) && checkBlock(game,x,y)), or 0 o.w
 */
int checkLegal(Game* game,int x, int y, int value);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param x - the column of the cell
 * @param y - the row of the cell
 * @param value - the value to be checked if legal in column x, row y
 * @return 1 if value is legal in column x and in row y, or 0 o.w
 */
int checkRowColumn(Game *game, int x, int y, int value);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param index - and index in the array that represents the board
 * @param a - an array of size 2 that saves the (x,y) coordinates
 * @return 0
 */
int position(Game* game ,int index,int*a);

/**
 *
 * @param game - a pointer to the current Game instance
 * @return i from range [0,boardSize-1] so that gameBoard[i].isFixed == 0
 */
int findFirstNotFixed(Game* game);

/**the function calls a deallocation function to free game and prints an exit message
 *
 * @param game - a pointer to the current Game instance
 * @return -1
 */
int exitGame(Game* game);


/**
 *
 * @param game - a pointer to the current Game instance
 * @param solution - an int array that represents the game solution
 * @param pastValues - an array that holds for solution(x,y), the values that were already tried to be set
 * @param x - the column of the cell
 * @param y - the row of the cell
 * @param values - the array that holds all the possible values for solution(x,y)
 * @pre values[0] == size(values)-1
 * @pre pastValues[0] == size(pastValues)-1
 * @post values[0] == size(values)-1
 * @return values
 */
int *getAllPossibleValues(Game* game,int* solution,int*pastValues, int x,int y,int*values);

/**
 *
 * @param game - a pointer to the current Game instance
 * @return a replica of game->solution
 */
int* duplicateSol(Game*game);

/**
 *
 * @param game - a pointer to the current Game instance
 * @return 1 if the game is in a winning state, or 0 o.w
 */
int winningBoard(Game* game);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param sol - an array that represents the solution of the generated puzzle
 * @param x - the column of a cell
 * @param y - the row of a cell
 * @param value - the value to be checked
 * @return 1 if(checkBlockSol(game,x,y,value) && checkRowColumnSol(game,x,y,value)), or 0 o.w
 */
int checkLegalSol(Game* game,int* sol ,int x, int y, int value);

/**
 *
 * @param game - a pointer to the current Game instance
 * @param sol - an array that represents the solution of the generated puzzle
 * @param x - the column of a cell
 * @param y - the row of a cell
 * @param value - the value to be checked
 * @return 1 the block that contains (x,y) doesn't contain value, or 0 o.w
 */
int checkBlockSol(Game* game, int* sol, int x, int y, int value);

int checkRowColumnSol(Game* game, int* sol, int x, int y, int value);

int addHints(Game*game,int hints);

#endif
