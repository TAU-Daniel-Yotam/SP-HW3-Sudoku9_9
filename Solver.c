#include "Solver.h"
#include <stdlib.h>
#include "MainAux.h"
#include "Game.h"


int detSolve(Game* game){
    int i = findFirstNotFixed(game);
    int*newSol=duplicateSol(game);
    return detSolveRec(game,newSol,i,i);
}

int detSolveRec(Game* game,int*solution,int start, int index){
    int size = game->blockWidth*game->blockHeight;
    int*pos;/* length(position=2 */
    int rightMove;
    if(index == start && size)
        return 0;
    if(index == size*size){
        free(game->solution);
        game->solution=solution;
        return 1;
    }
    if(game->board[index].isFixed || game->board[index].isPlayerMove)/*יש פה מעגל!!!!!!*/
        return detSolveRec(game, solution, start, index+1);
    pos = position(game,index);
    rightMove= findRightMove(game,pos[0],pos[1],solution[index]+1);
    if(rightMove){
        solution[index]=rightMove;
        return detSolveRec(game,solution,start,index+1);
    }else{
        solution[index]=0;
        return detSolveRec(game,solution,start,index-1);
    }


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

int randSolveRec(Game* game, int* solution,int start, int index, int**options){
    int size = game->blockWidth*game->blockHeight;
    int*pos = position(game,index);/* length(position=2 */
    if(index == start && size)
        return 0;
    if(index == size*size){
        free(game->solution);
        game->solution=solution;
        return 1;
    }
    if(game->board[index].isFixed || game->board[index].isPlayerMove)
        return randSolveRec(game, solution, start, index+1,options);
    int*values = getAllPossibleValues(game,options[index],pos[0],pos[1]);
    if(values==NULL){
        options[index]=NULL;
        return randSolveRec(game,solution,start,index-1,options);/*יש פה מעגל!!!!!!*/
    }
    if(values!={0}){
        int valuesSize = sizeof(values)/ sizeof(int);
        int optionsSize = sizeof(options[index])/ sizeof(int);
        int i = rand()%valuesSize;
        options[index] = realloc(options[index],(optionsSize+1)* sizeof(int));/* check if realloc succeeded*/
        options[index][optionsSize] = values[i];
        solution[index]=values[i];
        return randSolveRec(game, solution, start, index+1,options);
    }
    return -1;
}