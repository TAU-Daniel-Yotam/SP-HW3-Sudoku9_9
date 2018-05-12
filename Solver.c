#include "Solver.h"
#include <stdlib.h>
#include "MainAux.h"
#include "Game.h"

int detSolveRec(Game* game,int*solution,int start, int index, int moveDir);
int findRightMove(Game* game, int x, int y, int from);
int randSolveRec(Game* game, int* solution,int start, int index, int**options,int moveDir);

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
    if(index == start && size)
        return 0;
    if(index == size*size){
        free(game->solution);
        game->solution=solution;
        return 1;
    }
    if(game->board[index].isFixed || game->board[index].isPlayerMove)/*יש פה מעגל!!!!!!*/
        return detSolveRec(game, solution, start, index+moveDir,moveDir);
    position(game,index,pos);
    rightMove= findRightMove(game,pos[0],pos[1],solution[index]+1);
    if(rightMove){
        solution[index]=rightMove;
        return detSolveRec(game,solution,start,index+1,1);
    }else{
        solution[index]=0;
        return detSolveRec(game,solution,start,index-1,-1);
    }


}


int findRightMove(Game* game, int x, int y, int from) {
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
    return randSolveRec(game,solution,0,0,options,1);
}

/*Pre:
 *  moveDir == 1 if moving right, -1 if moving left
 *  options[i][0] == (num of elements in options[i])-1
 *
 *Post: ret==1 if solution found
 *      ret==0 if current game is unsolvable
 *      ret==-1 if a memory allocation error occurred*/
int randSolveRec(Game* game, int* solution,int start, int index, int**options,int moveDir){
    int pos[2];
    int size = game->blockWidth*game->blockHeight;
    int*values={0};
    position(game,index,pos);/* length(position)==2 */
    if(index == start && size)
        return 0;
    if(index == size*size){
        free(game->solution);
        game->solution=solution;
        return 1;
    }
    if(game->board[index].isFixed || game->board[index].isPlayerMove)
        return randSolveRec(game, solution, start, index+moveDir,options,moveDir);

    values = getAllPossibleValues(game,options[index],pos[0],pos[1],values);
    if(values[0]==0){
        options[index]=NULL;
        return randSolveRec(game,solution,start,index-1,options,-1);
    }
    if(values[0]==1){
        int optionsSize = options[index][0];
        options[index] = realloc(options[index],(optionsSize+1)* sizeof(int));
        if(options[index]==NULL) return -1;
        options[index][0]+=1;
        options[index][optionsSize] = values[1];
        solution[index]=values[1];
        return randSolveRec(game, solution, start, index+1,options,1);
    }
    if(values[0]>1){
        int valuesSize = values[0];
        int optionsSize = options[index][0];
        int i = rand()%valuesSize;
        options[index] = realloc(options[index],(optionsSize+1)* sizeof(int));
        if(options[index]==NULL) return -1;
        options[index][0]+=1;
        options[index][optionsSize] = values[i];
        solution[index]=values[i];
        return randSolveRec(game, solution, start, index+1,options,1);
    }

    return -1;
}
