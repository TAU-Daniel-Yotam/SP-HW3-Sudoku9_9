
#include "Solver.h"
#include "Game.h"
#include <stdlib.h>


int findFirstNotFixed(Game game) {
	int i = 0;
	for ( ; i < game.boardSize; i++) {
		if (game.board[i].isFixed != 1 && game.board[i].isPlayerMove != 1) {
            return i;
		}
	}
	return i;
}


int detSolve(Game game) {
	int rightMove = 0;
	int * positionXY;
	int indexOfgame = 0;
	while (indexOfgame < game.boardSize) {
		if (indexOfgame == findFirstNotFixed(game) && game.board[indexOfgame].value == Block_Height * Block_Width) {
			return	0;
		}
		if (game.board[indexOfgame].isFixed || game.board[indexOfgame].isPlayerMove) {
			indexOfgame++;
			continue;

		}
		else {
			positionXY = position(game,indexOfgame);
			rightMove = findRightMove(game, positionXY[1], positionXY[0], game.solution[indexOfgame] + 1);
			if (rightMove != 0) {
                game.solution[indexOfgame] = rightMove;
				indexOfgame++;
				continue;
			}
			else {
				game.solution[indexOfgame] = 0;
				indexOfgame--;
				continue;
			}

		}

	}
	return 1;
}

int findRightMove(Game game, int x, int y, int from) {
	int rightmove = 0;
	while (from <= Block_Height * Block_Width) {
		if (checkBlock(game, x, y, from) && checkRowColumn(game, x, y, from)) {
			rightmove = from;
			break;
		}
		from++;

	}
		return rightmove;
	}



/*Pre: board is empty
 *Post:
 *  return = 0 if function failed, or 1 o.w
 *  game.solution is solved*/
int randomSolve(Game game){

}

