#include "Solver.h"
#include <stdlib.h>

int deallocOptions(Game*game,int**options);

int detSolve(Game* game){
    int i = findFirstNotFixed(game);
    int*newSol=duplicateSol(game);
    return detSolveRec(game,newSol,i,i,1);
}

/*Pre: moveDir == 1 if moving right, -1 if moving left */
int detSolveRec(Game* game,int*solution,int start, int index, int moveDir){
    int size = game->blockWidth*game->blockHeight;
    int pos[2];/* length(position=2 */
    int rightMove;
    if(index == start && solution[index]==game->blockHeight*game->blockWidth)
        return 0;
    if(index == size*size){
        free(game->solution);
        game->solution=solution;
        return 1;
    }
    if(game->board[index].isFixed || game->board[index].isPlayerMove)
        return detSolveRec(game, solution, start, index+moveDir,moveDir);
    position(game,index,pos);
    rightMove= findRightMove(game,solution,pos[0],pos[1],solution[index]+1);
    if(rightMove){
        solution[index]=rightMove;
        return detSolveRec(game,solution,start,index+1,1);
    }else{
        solution[index]=0;
        return detSolveRec(game,solution,start,index-1,-1);
    }


}


int findRightMove(Game* game,int * solution, int x, int y, int from) {
    int rightMove = 0;
    while (from <= Block_Height * Block_Width) {
        if (checkBlockSol(game,solution, x, y, from) && checkRowColumnSol(game,solution, x, y, from)) {
            rightMove = from;
            break;
        }
        from++;

    }
    return rightMove;
}



/*Pre: board is empty
 *Post:
 *  return == 0 if function failed, or 1 o.w
 *  game.solution is solved*/
int randomSolve(Game* game){
    int i;
    int** options;
    int*solution;
    options=calloc(game->boardSize, sizeof(int));
    if(options==NULL) return 0;
    solution=calloc((unsigned int)game->boardSize, sizeof(int));
    if(solution==NULL) return 0;
    for(i=0;i<game->boardSize;i++){
        options[i]=(int*)calloc(1, sizeof(int*));
    }
    return randSolveRec(game,solution,0,0,options);
}

/*Pre:
 *  moveDir == 1 if moving right, -1 if moving left
 *  options[i][0] == (num of elements in options[i])-1
 *
 *Post: ret==1 if solution found
 *      ret==0 if current game is unsolvable
 *      ret==-1 if a memory allocation error occurred*/
int randSolveRec(Game* game, int* solution,int start, int index, int**options){
	int pos[2];
    int size = game->blockWidth*game->blockHeight;
    int*values=(int*)calloc(1,sizeof(int));
	values[0] = -1;
    position(game,index,pos);/* length(position)==2 */
	/*values = getAllPossibleValues(game, solution, options[index], pos[0], pos[1], values);*/
	if (index == start && values[0]==-1){
        deallocOptions(game,options);
        free(solution);
        free(values);
        return 0;
	}
    if(index == game->boardSize+1){
        free(game->solution);
        game->solution=solution;
        printArray(solution,game->boardSize);
        deallocOptions(game,options);
        free(values);
        return 1;
    }
    /*if(game->board[index].isFixed || game->board[index].isPlayerMove)
        return randSolveRec(game, solution, start, index+moveDir,options,moveDir);*/

   /* printArray(options,game->boardSize);
    printArray(options[index],options[index][0]+1);*/

    values = getAllPossibleValues(game,solution,options[index],pos[0],pos[1],values);
    /* debug
    printArray(values,values[0]+1);
    end debug*/
    if(values[0]==-1 && index!=start){
        free(options[index]);
        options[index]=(int*)calloc(1, sizeof(int));
        options[index][0]=0;
		solution[index] = 0;
		free(values);
        return randSolveRec(game,solution,start,index-1,options);
    }
    if(values[0]==1){
        int optionsSize = options[index][0];
        options[index] = realloc(options[index],(optionsSize+1)* sizeof(int));
        if(options[index]==NULL) return -1;
        options[index][0]+=1;
        options[index][optionsSize] = values[1];
        solution[index]=values[1];
        free(values);
        return randSolveRec(game, solution, start, index+1,options);
    }
    if(values[0]>1){
        int valuesSize = values[0];
        int optionsSize = options[index][0]+1;
        int i = rand()%valuesSize+1;
        options[index] = realloc(options[index],(optionsSize+1)* sizeof(int));
        if(options[index]==NULL) return -1;
        options[index][0]+=1;
        options[index][optionsSize] = values[i];
        solution[index]=values[i];
        /* debug
        printArray(options[index],options[index][0]+1);
        printArray(solution,game->boardSize);
        end debug */
        free(values);
        return randSolveRec(game, solution, start, index+1,options);
    }

    return -1;
}

int deallocOptions(Game*game,int**options){
    int i;
    for(i=0;i<game->boardSize;i++){
        free(options[i]);
    }
    free(options);
    return 0;
}