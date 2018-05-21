#include "Game.h"
#include <stdlib.h>


Game* getGameInitParams(Game* game, Game*newGame, int w, int h) {
	int size,hints,eof,successRandSolve;
	char c;
	Cell *gameBoard;
	int *solution;
	if (game != NULL) dealloc(game);
	size = w * h*w*h;
	printf("Please enter the number of cells to fill [0-%d]:\n", size - 1);
	while ((eof=scanf("%d%c", &hints, &c)) != 2) {
		if(eof==EOF) {
			printf("Exiting...\n");
			return NULL;
		}
		printf("Error: Invalid number of cells to fill (should be between 0 and %d)\n", size);
		printf("Please enter the number of cells to fill [0-%d]:\n", size - 1);
	}
	if ((gameBoard = (Cell*)calloc((unsigned int)size, sizeof(Cell))) == NULL) {
		printf("Error: calloc has failed\n");
		return NULL;
	}
	if ((solution = (int*)calloc((unsigned int)size, sizeof(int))) == NULL) {
		printf("Error: calloc has failed\n");
		return NULL;
	}
	newGame->blockHeight = h;
	newGame->blockWidth = w;
	newGame->solution = solution;
	newGame->board = gameBoard;
	newGame->boardSize = size;
	successRandSolve=randomSolve(newGame);
	if(successRandSolve==-1) return NULL;
	addHints(newGame, hints);

	return newGame;
}

int getBoardIndex(Game* game, int x, int y) {
	return game->blockHeight*game->blockWidth*(y - 1) + (x - 1);
}

int checkLegal(Game* game, int x, int y, int value) {
	return checkBlock(game, x, y, value)*checkRowColumn(game, x, y, value);
}

int checkBlock(Game* game, int x, int y, int value) {
	int k, r;
	int boardIndex = getBoardIndex(game, x, y);
	int blockStart, s;
	while (x%game->blockWidth != 1)x--;
	while (y%game->blockHeight != 1)y--;
	blockStart = getBoardIndex(game, x, y);
	s = blockStart;
	for (k = 0; k<game->blockHeight; k++) {
		for (r = 0; r<game->blockWidth; r++) {
			if (game->board[s].value == value && s != boardIndex)
				return 0;
			blockStart++;
		}
		s = blockStart + game->blockWidth*game->blockHeight - 1;
	}
	return 1;
}

int checkRowColumn(Game* game, int x, int y, int value) {
	int index = getBoardIndex(game, x, y);
	int line = getBoardIndex(game, 1, y);
	int l = line;
	int row = getBoardIndex(game, x, 1);

	for (; l < line + game->blockHeight*game->blockWidth; l++) {
		if (game->board[l].value == value) {
			if (l != index) {
				return 0;
			}
		}
	}
	for (; row < game->boardSize; row += (game->blockHeight*game->blockWidth)) {
		if (game->board[row].value == value) {
			if (row != index) {
				return 0;

			}
		}
	}
	return 1;
}

int checkLegalSol(Game* game, int*sol, int x, int y, int value) {
	return checkBlockSol(game, sol, x, y, value)*checkRowColumnSol(game, sol, x, y, value);
}

int checkBlockSol(Game* game, int* sol, int x, int y, int value) {
	int k, r;
	int boardIndex = getBoardIndex(game, x, y);
	int blockStart, s;
	while (x%game->blockWidth != 1)x--;
	while (y%game->blockHeight != 1)y--;
	blockStart = getBoardIndex(game, x, y);
	s = blockStart;
	for (k = 0; k<game->blockHeight; k++) {
		for (r = 0; r<game->blockWidth; r++) {
			if (sol[s] == value && s != boardIndex)
				return 0;
			s++;
		}
		blockStart = s + game->blockWidth*game->blockWidth - game->blockWidth;
		s = blockStart;
	}
	return 1;
}

int checkRowColumnSol(Game* game, int* sol, int x, int y, int value) {
	int index = getBoardIndex(game, x, y);
	int line = getBoardIndex(game, 1, y);
	int l = line;
	int row = getBoardIndex(game, x, 1);

	for (; l < line + game->blockHeight*game->blockWidth; l++) {
		if (sol[l] == value) {
			if (l != index) {
				return 0;
			}
		}
	}
	for (; row < game->boardSize; row += (game->blockHeight*game->blockWidth)) {
		if (sol[row] == value) {
			if (row != index) {
				return 0;

			}
		}
	}
	return 1;
}

/*a[0]=x, a[1]=y*/
int position(Game* game, int index, int*a) {
	int i = 1;
	int line = game->blockWidth*game->blockHeight - 1;
	while (index > line) {
		line += game->blockWidth*game->blockHeight;
		i += 1;
	}
	a[0] = index % (game->blockHeight*game->blockWidth) + 1;
	a[1] = i;
	return 0;
}

int findFirstNotFixed(Game* game) {
	int i = 0;
	for (; i < game->boardSize; i++) {
		if (game->board[i].isFixed != 1 && game->board[i].isPlayerMove != 1) {
			return i;
		}
	}
	return i;
}

int *getAllPossibleValues(Game* game, int* solution, int*pastValues, int x, int y, int*values) {
	int i, k = 1;
	if (values[0] == -1)
		values[0] = 0;
	for (i = 1; i <= game->blockWidth*game->blockHeight; i++) {
		if (checkLegalSol(game, solution, x, y, i) && !inArray(pastValues, pastValues[0]+1, i)) {
			values = (int *)realloc(values, (k + 1) * sizeof(int));
			if (values == NULL) {
				return NULL;
			}
			values[0] = k;
			values[k] = i;
			k++;
		}
	}
	return values;
}


int set(Game* game, int x, int y, int  value) {
    int index;
	if(x==-1 || y==-1 || value==-1){
		printf("Error: invalid command\n");
		return winningBoard(game);
	}
	index = getBoardIndex(game, x, y);
	if (game->board[index].isFixed) {
		printf("Error: cell is fixed\n");
	}
	else if (value == 0) {
		game->board[index].value = 0;
		printBoard(game);
	}
	else if (game->solution[index] == value && value != -1) {
		game->board[index].value = value;
		game->board[index].isPlayerMove = 1;
		printBoard(game);
	}
	else if (checkBlock(game, x, y, value) && checkRowColumn(game, x, y, value) && value != -1) {
		game->board[index].value = value;
		game->board[index].isPlayerMove = 1;
		printBoard(game);
	}
	else {
		printf("Error: value is invalid\n");
	}
	return winningBoard(game);


}

int validate(Game* game) {
	if (detSolve(game)) {
		printf("Validation passed: board is solvable\n");
		return 1;
	}
	else {
		printf("Validation failed: board is unsolvable\n");
	}
	return 0;

}
int hint(Game * game, int x, int y) {
    int index;
	if(x==-1 || y==-1) {
		printf("Error: invalid command\n");
		return 0;
	}
	index = getBoardIndex(game, x, y);
	printf("Hint: set cell to %d\n", game->solution[index]);
	return 0;
}

int winningBoard(Game* game) {
	int i;
	for (i = 0; i< game->boardSize; i++) {
		if (!game->board[i].value) {
			return 0;
		}
	}
	return 1;
}

int exitGame(Game* game) {
	dealloc(game);
	printf("Exiting...\n");
	return -1;
}

int* duplicateSol(Game*game) {
	int i;
	int*sol = calloc((unsigned int)game->boardSize, sizeof(int));
	if (sol == NULL) return NULL;
	for (i = 0; i<game->boardSize; i++) {
		sol[i] = game->board[i].value;
	}
	return sol;
}


int addHints(Game*game, int hints) {
	int x, y, i, index;
	i = 0;
	while (i<hints) {
		x = rand() % (game->blockHeight*game->blockWidth) + 1;
		y = rand() % (game->blockHeight*game->blockWidth) + 1;
		index = getBoardIndex(game, x, y);
		if (!game->board[index].isFixed) {
			game->board[index].value = game->solution[index];
			game->board[index].isFixed = 1;
			i++;
		}
	}
	return 0;
}