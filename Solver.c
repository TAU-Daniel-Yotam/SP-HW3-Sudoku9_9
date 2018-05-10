
#include "Solver.h"
#include "Game.h"
#include <stdlib.h>
#include "MainAux.h"


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
	int rightMove = 0;
	while (from <= Block_Height * Block_Width) {
		if (checkBlock(game, x, y, from) && checkRowColumn(game, x, y, from)) {
			rightMove = from;
			break;
		}
		from++;

	}
		return rightMove;
	}



/*Pre: board is empty
 *Post:
 *  return = 0 if function failed, or 1 o.w
 *  game.solution is solved*/
int randomSolve(Game game){

}

int randBackTrack(Game game, int index, int startIndex){
    int*coordinates = position(game,index);
    int*values = getAllPossibleValues(game,coordinates[1],coordinates[0]);
    int size = calcSizeOfArray(values);

}