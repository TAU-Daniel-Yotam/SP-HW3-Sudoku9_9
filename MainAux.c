

#include "MainAux.h"
#include <stdlib.h>

int getRandomInt(int bound){
    return 1+rand()%bound;
}

int calcSizeOfArray(int*a){
    return sizeof(a)/ sizeof(int);
}

void printboard(Game game) {
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
                if (game.board[getBoardIndex(game, j, i)].isFixed) {
                    printf(" .%d", game.board[getBoardIndex(game, j, i)].value);
                }
                else {

                    if (game.board[getBoardIndex(game, j, i)].value != 0) {
                        printf(" %d", game.board[getBoardIndex(game, j, i)].value);
                    }

                    else {
                        printf("   ", game.board[getBoardIndex(game, j, i)].value);

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