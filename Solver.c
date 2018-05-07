
#include "Solver.h"
#include "Game.h"


int checkRowColumn(Game game,int x, int y, int value){
    return 0;
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

int getBoardIndex(Game game, int x, int y){
    return game.blockHeight*game.blockWidth*(y-1)+(x-1);
}

int checkLegal(Game game,int x, int y, int value){
    return checkBlock(game,x,y,value)*checkRowColumn(game,x,y,value);
}

/*Pre: board is empty
 *Post:
 *  return = 0 if function failed, or 1 o.w
 *  game.solution is solved*/
int randomSolve(Game game){

}

