
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Parser.h"
#include "MainAux.h"
#include "Game.h"
# define Block_Width 3
# define Block_Height 3


int main(int argc, char * argv[]) {
	int exit, restart, selection, counter, argLen, arg, eof;
	int parsedCommand[4];
	char command[1024];
	Game game;
	Game* gameP;
	initArray(parsedCommand,4,-1);
	argLen = parseSize(argv[argc - 1]);
	arg = parseInt(argv[argc - 1], argLen);
	srand(arg);
	exit = 0;
	restart = 1;
	while (!exit) {

		if (restart) {
			if(gameP!=NULL){
				gameP = getGameInitParams(gameP, &game, Block_Height, Block_Width);
			}
			else
				gameP = getGameInitParams(NULL, &game, Block_Height, Block_Width);
			if(gameP==NULL) return 0;
			game=*gameP;
			printBoard(&game);
			restart = 0;
		}
		eof=getInput(command, 1024);
		if(eof) selection =5;
		else 	selection = parseCommand(command, parsedCommand);
		switch (selection) {
		case 1:
			if (set(&game, parsedCommand[1], parsedCommand[2], parsedCommand[3])) {
				counter = 1;
				do {
					if (counter == 1) {
						printf("Puzzle solved successfully\n");
						counter = 2;
					}
					else if (counter == 2){
						printf("Error: invalid command\n");
					}
					getInput(command, 1024);
					selection = parseCommand(command, parsedCommand);
				} while (selection != 4 && selection != 5);
				if (selection == 4)
					restart = 1;
				else {
					exit = 1;
					exitGame(&game);

				}
			}
			break;
		case 2:
			hint(&game, parsedCommand[1], parsedCommand[2]);
			break;
		case 3:
			validate(&game);
			break;
		case 4:
			restart = 1;
			break;
		case 5:
			exitGame(&game);
			exit = 1;
			break;
		default:
			printf("Error: invalid command\n");
			break;
		}
		initArray(parsedCommand,4,-1);
	}
	return 0;
}



