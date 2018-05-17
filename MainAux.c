
#include "MainAux.h"
#include <stdlib.h>



void printBoard(Game* game) {
	int i, j;
	int index = 0;
	for (i = 0; i < game->blockHeight*game->blockWidth; i++) {
		if (!(i%game->blockHeight))
			printf("----------------------------------\n");
		for (j = 0; j < game->blockHeight*game->blockWidth; j++) {
			if (!(j%game->blockWidth)) {
				if (!j)
					printf("|");
				else
					printf(" |");
			}
			index = getBoardIndex(game, j + 1, i + 1);
			if (game->board[index].isFixed) {
				printf(" .%d", game->board[getBoardIndex(game, j + 1, i + 1)].value);
			}
			else {

				if (game->board[getBoardIndex(game, j + 1, i + 1)].value != 0) {
					printf("  %d", game->board[getBoardIndex(game, j + 1, i + 1)].value);
				}

				else {
					printf("   ");

				}
			}
		}
		printf(" |\n");

	}
	printf("----------------------------------\n");
}


int dealloc(Game* game) {
	free(game->solution);
	free(game->board);
	return 0;
}

int inArray(int*a, int size, int v) {
	int i;
	for (i = 0; i<size; i++) {
		if (v == a[i]) return 1;
	}
	return 0;
}

int compareArrays(int*a, int sizeA, int*b, int sizeB) {
	int i;
	if (sizeA != sizeB) return 0;
	for (i = 0; i<sizeA; i++) {
		if (a[i] != b[i]) return 0;
	}
	return 1;
}

void printArray(void*a, int size) {
	int i;
	int*x = (int*)a;
	for (i = 0; i<size; i++) {
		printf("a[%d]=%d ", i, x[i]);
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
}