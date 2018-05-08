

#ifndef Game_h
#define Game_h

#include <stdio.h>

#endif /* Game_h */

# define Block_Width 3
# define Block_Height 3

/*Cell struct*/
typedef struct Cell{
    int value;
    int isFixed;
    int isPlayerMove;
} Cell;
#define line_len 0


typedef struct Game{
    int blockWidth;
    int blockHeight;
    Cell* board;
	int boardSize;
    int* solution;
    int isSolveable;
} Game;

int getGameInitParams();

Cell* createEmptyBoard(int x, int y);

int printBoard(Cell* board, int size);

int generatePuzzle(Cell* board, int size);

int checkBlock(Game game,int x, int y, int value);

int getBoardIndex(Game game, int x, int y);

int checkLegal(Game game,int x, int y, int value);

int checkRowColumn(Game game, int x, int y, int value);

int* position(Game game ,int index);

int findFirstNotFixed(Game game);

/*Pre: y,x<=game.blockWidth * blockHeight
 *Post: ret={i|1<=i<=blockWidth * blockHeight && i is a legal value in (x,y)}*/
int*getAllPossibleValues(Game game, int x,int y);


