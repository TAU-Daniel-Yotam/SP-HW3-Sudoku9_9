

#include "Game.h"
#include "Solver.h"
#include <stdlib.h>
# define Block_Width 3
# define Block_Height 3


int getGameInitParams(){
    unsigned int size=Block_Width*Block_Width*Block_Height*Block_Height;
    int hints;
    char c;
    Cell *gameBoard;
    Cell *solution;
    printf("Please enter the number of cells to fill [0-%d]:\n",size-1);
    while(scanf("%d%c",&hints,&c)!=2){
        printf("Error: Invalid number of cells to fill (should be between 0 and %d)\n",size);
        printf("Please enter the number of cells to fill [0-%d]:\n",size-1);
    }
    if((gameBoard =(Cell*)calloc(size,sizeof(Cell)))==NULL){
        printf("Error: calloc has failed\n");
        return 0;
    }
    /* generate a random puzzle to "solution"
     fill "gameBoard" puzzle with hints*/
}


Cell* createEmptyBoard(int x, int y){
    
}
int printBoard(Cell* board, int size){
    
}
