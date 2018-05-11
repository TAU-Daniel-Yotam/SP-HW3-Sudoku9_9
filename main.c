
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include"game.h"
# define Block_Width 3
# define Block_Height 3


/*const char * argv[]*/
int main(int argc) {
	Game game;
	srand(argc);
	int exit=0;
	int restart = 1;
	int selection;
	int counter;
	int parsedCommand[4] = { 6 };
	char command[1024];
	int winning = 0;
	while (!exit) {

		if (restart) {
			getGameInitParams(&game, Block_Height, Block_Height);
			restart = 0;
		}
		printBoard(game.board, game.boardSize);
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
					}
					if (counter == 2)
						printf("Error: invalid command\n");
					selection = parseCommand(command, parsedCommand);
				} while (selection != 4 | selection != 5);
				if (selection == 4)
					restart = 1;
				else{
					exit = 1;
					exitGame(&game);

			}
		case 2:
			hint(&game, parsedCommand[1], parsedCommand[2]);
		case 3:
			validate(game);
		case 4:
			restart = 1;
		case 5:
			exitGame(&game);
			exit = 1;
		case 6:
			printf("Error: invalid command\n");

		}

	}
}

	return 0;

	
}

