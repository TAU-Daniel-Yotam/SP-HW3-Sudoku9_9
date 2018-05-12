

#include "MainAux.h"
#include <stdlib.h>



void printBoard(Game* game) {
    for (int i = 0; i < Block_Height*Block_Width; i++) {
        if (!(i%Block_Height)) {
            printf("----------------------------------\n");
            for (int j = 0; i < Block_Height*Block_Width; j++) {

                if (!(j%Block_Width)) {
                    if (!j)
                        printf(" |");
                    else
                        printf("|");

                }
                if (game->board[getBoardIndex(game, j, i)].isFixed) {
                    printf(" .%d", game->board[getBoardIndex(game, j, i)].value);
                }
                else {

                    if (game->board[getBoardIndex(game, j, i)].value != 0) {
                        printf(" %d", game->board[getBoardIndex(game, j, i)].value);
                    }

                    else {
                        printf("   ", game->board[getBoardIndex(game, j, i)].value);

                    }
                }
            }
            printf(" |\n");

        }
    }
    printf("----------------------------------\n");
}

int dealloc(Game* game){
    free(game->solution);
    free(game->board);
}

int inArray(int a[],int v){
    int size = sizeof(a)/ sizeof(int);
    int i;
    for(i=0;i<size;i++){
        if(v==a[i]) return 1;
    }
    return 0;
}

int compareArrays(int*a,int sizeA, int*b, int sizeB){
    int i;
    if(sizeA!=sizeB) return 0;
    for(i=0;i<sizeA;i++){
        if(a[i]!=b[i]) return 0;
    }
    return 1;
}