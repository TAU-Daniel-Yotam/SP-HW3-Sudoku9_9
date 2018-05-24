#include "Solver.h"
#include <stdlib.h>
#include <assert.h>

int deallocOptions(Game*game, int**options);

int detSolve(Game* game) {
	int i = findFirstNotFixed(game);
	int*newSol = duplicateSol(game);
	return detSolveRec(game, newSol, i);
}

/*Pre: moveDir == 1 if moving right, -1 if moving left */
int detSolveRec(Game* game, int*solution, int index) {
    int rightMove, solved;
    int size = game->blockWidth * game->blockHeight * game->blockWidth * game->blockHeight;
    int pos[2];/* length(position)=2 */
	while((game->board[index].isFixed || game->board[index].isPlayerMove) && index<size){
		index++;
	}
    solved=0;
    position(game,index,pos);
    if (index == size) {
        free(game->solution);
        game->solution = solution;
        return 1;
    }
    while((rightMove=findRightMove(game,solution,pos[0],pos[1],solution[index]+1)) && !solved){
        solution[index]=rightMove;
        solved = detSolveRec(game,solution,index+1);
        if(!solved) continue;
        return solved;
    }
    if(!rightMove){
        solution[index]=0;
        return 0;
    }
	return 1;

}


int findRightMove(Game* game, int * solution, int x, int y, int from) {
	int rightMove = 0;
	while (from <= game->blockHeight*game->blockWidth) {
		if (checkBlockSol(game, solution, x, y, from) && checkRowColumnSol(game, solution, x, y, from)) {
			rightMove = from;
			break;
		}
		from++;

	}
	return rightMove;
}



int randomSolve(Game* game) {
	int i;
	int** options;
	int*solution;
	options = calloc(game->boardSize, sizeof(int*));
	if (options == NULL) {
		printf("Error: calloc has failed\n");
		return -1;
	}
	solution = calloc((unsigned int)game->boardSize, sizeof(int));
	if (solution == NULL) {
		printf("Error: calloc has failed\n");
		return -1;
	}
	for (i = 0; i<game->boardSize; i++) {
		options[i] = (int*)calloc(1, sizeof(int*));
		if(options[i]==NULL){
			printf("Error: calloc has failed\n");
			return -1;
		}
	}
	return randSolveRec(game, solution, 0, 0, options);
}

/*Pre:
*  moveDir == 1 if moving right, -1 if moving left
*  options[i][0] == (num of elements in options[i])-1
*
*Post: ret==1 if solution found
*      ret==0 if current game is unsolvable
*      ret==-1 if a memory allocation error occurred*/
int randSolveRec(Game* game, int* solution, int start, int index, int**options) {
	int pos[2];
	int*values = (int*)calloc(1, sizeof(int));
	if(values==NULL){
		printf("Error: calloc has failed\n");
		return -1;
	}
	/*values[0] = -1;*/
	position(game, index, pos);/* length(position)==2 */
	values = getAllPossibleValues(game, solution, options[index], pos[0], pos[1], values);
	if (index == start && values[0] == 0) {
		deallocOptions(game, options);
		free(solution);
		free(values);
		return 0;
	}
	if (index == game->boardSize) {
		free(game->solution);
		game->solution = solution;
		deallocOptions(game, options);
		free(values);
		return 1;
	}
	if (values[0] == 0 && index != start) {
		free(options[index]);
		options[index] = (int*)calloc(1, sizeof(int));
		if(options[index]==NULL){
			printf("Error: calloc has failed\n");
			return -1;
		}
		options[index][0] = 0;
		solution[index] = 0;
		free(values);
		return randSolveRec(game, solution, start, index - 1, options);
	}
	if (values[0] == 1) {
        int optionsSize = options[index][0]+1;
		options[index] = realloc(options[index], (optionsSize + 1) * sizeof(int));
		if(options[index]==NULL){
			printf("Error: calloc has failed\n");
			return -1;
		}
		options[index][0] += 1;
		options[index][optionsSize] = values[1];
		solution[index] = values[1];
		free(values);
		return randSolveRec(game, solution, start, index + 1, options);
	}
	if (values[0]>1) {
		int valuesSize = values[0];
		int optionsSize = options[index][0] + 1;
		int i = rand() % valuesSize + 1;
		options[index] = realloc(options[index], (optionsSize + 1) * sizeof(int));
		if(options[index]==NULL){
			printf("Error: realloc has failed\n");
			return -1;
		}
		options[index][0] += 1;
		options[index][optionsSize] = values[i];
		solution[index] = values[i];
		free(values);
		return randSolveRec(game, solution, start, index + 1, options);
	}

	return -1;
}

int deallocOptions(Game*game, int**options) {
	int i;
	for (i = 0; i<game->boardSize; i++) {
		free(options[i]);
	}
	free(options);
	return 0;
}