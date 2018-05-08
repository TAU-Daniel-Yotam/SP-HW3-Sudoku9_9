
#include "Solver.h"
#include "Game.h"
#include <stdlib.h>


int checkRowColumn(Game game, int x, int y, int value) {
	int index = getBoardIndex(game, x, y);
	int  line = getBoardIndex(game, 0, y);
	int row = getBoardIndex(game, x, 0);
	for (line; line < line + line_len; line++) {
		if (game.board[line].value == value) {
			if (line != index) {
				return 0;
			}
		}
	}
	for (row; row < game.boardSize; row+line_len ) {
		if (game.board[row].value == value) {
			if (row != index) {
				return 0;

			}



		}

	}
	return 1;
}
   

int checkBlock(Game game,int x, int y, int value){
    int k,r;
    int boardIndex = getBoardIndex(game,x,y);
    int blockStart;
    int s=blockStart;
    while(x%game.blockWidth!=0)x--;
    while(y%game.blockHeight!=0)y--;
    blockStart = getBoardIndex(game,x,y);
    for(k=0;k<game.blockHeight;k++){
        for(r=0;r<game.blockWidth;r++){
            if(game.board[s].value==value && s!=boardIndex)
                return 0;
            blockStart++;
        }
        s=blockStart+game.blockWidth*game.blockHeight-1;
    }
    return 1;

}
int findfirstNoFixed(Game game) {
	int i = 0;
	for (i; i < game.boardSize; i++) {
		if (game.board[i].isFixed != 1 || game.board[i].isPlayerMove != 1) {
			break;
		}
		return i;
	}
}

int getBoardIndex(Game game, int x, int y){
    return game.blockHeight*game.blockWidth*(y-1)+(x-1);
}

int checkLegal(Game game,int x, int y, int value){
    return checkBlock(game,x,y,value)*checkRowColumn(game,x,y,value);
}
Cell* deteSolve(Game game) {
	int rightMove = 0;
	int * positionXY;
	int indexOfgame = 0;
	while (indexOfgame <= game.boardSize) {
		if (indexOfgame == findfirstNoFixed(game) & game.board[indexOfgame].value == Block_Height * Block_Width) {
			return	NULL;
		}
		if (game.board[indexOfgame].isFixed || game.board[indexOfgame].isPlayerMove) {
			indexOfgame++;
			continue;

		}
		else {
			positionXY = position(indexOfgame);
			rightMove = findrightmove(game, positionXY[1], positionXY[0], game.board[indexOfgame].value + 1);
			if (rightMove != 0) {
				Cell num;
				strcpy(num.isFixed, 0);
				strcpy(num.isPlayerMove, 0);
				strcpy(num.value = rightMove);
				game.board[indexOfgame] = num;
				indexOfgame++;
				continue;
			}
			else {
				game.board[indexOfgame].value = 0;
				indexOfgame--;
				continue;
			}

		}

	
}

int findrightmove(Game game, int x, int y, int from) {
	int rightmove = 0;
	while (from <= Block_Height * Block_Width) {
		if (checkBlock(game, x, y, from)&checkRowColumn(game, x, y, from)) {
			rightmove = from;
			break;
		}
		from++;

	}
		return rightmove;
	}

int* position(int index) {
	int* a = calloc(2, sizeof(int));
	a[1] = index % line_len;
	a[0] = (index - a[1]) / line_len;


	return a;
}

/*Pre: board is empty
 *Post:
 *  return = 0 if function failed, or 1 o.w
 *  game.solution is solved*/
int randomSolve(Game game){

}

