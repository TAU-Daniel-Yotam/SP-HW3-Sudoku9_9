
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include "MainAux.h"
#include"Game.h"
# define Block_Width 3
# define Block_Height 3


/*const char * argv[]*/
int main(int argc,char * argv[]) {
	int exit;
	int restart;
	int selection;
	int counter;
	int parsedCommand[4] = {6};
	char command[1024];
	Game* game;
	srand(argc);
	exit = 0;
	restart = 1;
	game = getGameInitParams(NULL,Block_Width,Block_Height);
	while (!exit) {

		if (restart) {
			getGameInitParams(game, Block_Height, Block_Height);
			restart = 0;
		}
		printBoard(game);
		getInput(command, 1024);
		selection = parseCommand(command, parsedCommand);
		switch (selection) {
			case 1:
				if (set(game, parsedCommand[1], parsedCommand[2], parsedCommand[3])) {
					counter = 1;
					do {
						if (counter == 1) {
							printf("Puzzle solved successfully\n");
							counter = 2;
						} else if (counter == 2)
							printf("Error: invalid command\n");
						getInput(command, 1024);
						selection = parseCommand(command, parsedCommand);
					} while (selection != 4 && selection != 5);
					if (selection == 4)
						restart = 1;
					else {
						exit = 1;
						exitGame(game);

					}
				}
				break;
			case 2:
				hint(game, parsedCommand[1], parsedCommand[2]);
				break;
			case 3:
				validate(game);
				break;
			case 4:
				restart = 1;
				break;
			case 5:
				exitGame(game);
				exit = 1;
				break;
			default:
				printf("Error: invalid command\n");
				break;
		}
	}
	return 0;
}



