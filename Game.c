

#include "Game.h"
#include "Solver.h"
#include "MainAux.h"
#include <stdlib.h>




Game* getGameInitParams(Game* game, int w, int h){
    int size;
    int hints;
    char c;
    Cell *gameBoard;
    int *solution;
    if(game!=NULL) dealloc(game);
    size=w*h*w*h;
    printf("Please enter the number of cells to fill [0-%d]:\n",size-1);
    while(scanf("%d%c",&hints,&c)!=2){
        printf("Error: Invalid number of cells to fill (should be between 0 and %d)\n",size);
        printf("Please enter the number of cells to fill [0-%d]:\n",size-1);
    }
    if((gameBoard =(Cell*)calloc((unsigned int)size,sizeof(Cell)))==NULL){
        printf("Error: getGameInitParams has failed\n");
        return NULL;
    }
    if((solution =(int*)calloc((unsigned int)size,sizeof(int)))==NULL){
        printf("Error: getGameInitParams has failed\n");
        return NULL;
    }
    game->blockHeight=h;
    game->blockWidth=w;
    game->solution=solution;
    game->board=gameBoard;
    randomSolve(game);
    addHints(game);

    return game;
}


int checkBlock(Game* game,int x, int y, int value){
    int k,r;
    int boardIndex = getBoardIndex(game,x,y);
    int blockStart,s;
    while(x%game->blockWidth!=0)x--;
    while(y%game->blockHeight!=0)y--;
    blockStart = getBoardIndex(game,x,y);
    s=blockStart;
    for(k=0;k<game->blockHeight;k++){
        for(r=0;r<game->blockWidth;r++){
            if(game->board[s].value==value && s!=boardIndex)
                return 0;
            blockStart++;
        }
        s=blockStart+game->blockWidth*game->blockHeight-1;
    }
    return 1;

}

int getBoardIndex(Game* game, int x, int y){
    return game->blockHeight*game->blockWidth*(y-1)+(x-1);
}

int checkLegal(Game* game,int x, int y, int value){
    return checkBlock(game,x,y,value)*checkRowColumn(game,x,y,value);
}

int checkRowColumn(Game* game, int x, int y, int value) {
    int index = getBoardIndex(game, x, y);
    int  line = getBoardIndex(game, 1, y);
    int row = getBoardIndex(game, x, 1);
    for (line; line < line + game->blockHeight*game->blockWidth; line++) {
        if (game->board[line].value == value) {
            if (line != index) {
                return 0;
            }
        }
    }
    for (row; row < game->boardSize; row+=(game->blockHeight*game->blockWidth)) {
        if (game->board[row].value == value) {
            if (row != index) {
                return 0;

            }
        }
    }
    return 1;
}

/*a[0]=x, a[1]=y*/
int* position(Game* game ,int index,int*a) {
    a[1] = index % (game->blockHeight*game->blockWidth);
    a[0] = (index - a[1]) / (game->blockHeight*game->blockWidth);
    return a;
}

int findFirstNotFixed(Game* game) {
    int i = 0;
    for ( ; i < game->boardSize; i++) {
        if (game->board[i].isFixed != 1 && game->board[i].isPlayerMove != 1) {
            return i;
        }
    }
    return i;
}

int *getAllPossibleValues(Game* game,int*pastValues, int x,int y,int*values){
    int i,k=1;
    for(i=1;i<=game->blockWidth*game->blockHeight;i++) {
        if (checkLegal(game, x, y, i) && !inArray(pastValues,i)) {
            values = (int *) realloc(values, k * sizeof(int));
            if (values == NULL){
                return NULL;
            }
            values[0]=k;
            values[k] = i;
            k++;
        }
    }
    return values;
}


int set(Game* game,int x, int y, int  value) {

    int index = getBoardIndex(game, x, y);
    if (game->board[index].isFixed) {
        printf("Error: cell is fixed\n");
    }
    else if (value == 0) {
        game->board[index].value = 0;
    }
    else if (game->solution[index] == value) {
        game->board[index].value = value;
        game->board[index].isPlayerMove = 1;
        printBoard(game);
    }
    else if (checkBlock(game, x, y, value) && checkRowColumn(game, x, y, value)) {
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
    int index = getBoardIndex(game,x, y);
    printf("Hint: set cell to %d\n", game->solution[index]);
    return 0;
}

int winningBoard(Game* game) {
    int i;
    for (i = 0;i< game->boardSize; i++) {
        if (!game->board[i].value) {
            return 0;
        }
    }
    return 1;
}

int exitGame(Game* game){
    dealloc(game);
    free(game);
    printf("Exiting...\n");
    return -1;
}

int* duplicateSol(Game*game){
    int i;
    int*sol = calloc((unsigned int)game->boardSize,sizeof(int));
    if(sol==NULL) return NULL;
    for(i=0;i<game->boardSize;i++){
        sol[i]=game->solution[i];
    }
    return sol;
}
