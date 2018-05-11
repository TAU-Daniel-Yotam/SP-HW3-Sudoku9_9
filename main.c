
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include"game.h"
# define Block_Width 3
# define Block_Height 3


/*const char * argv[]*/
int main(int argc) {
	Game game;
	int restart = 1;
	int noexit = 1;
	int selection;
	int parsedCommand[4] = { 6 };
	char command[1024];
	int winning = 0;
	while (noexit) {

		if (restart) {
			getGameInitParams(&game, Block_Height, Block_Height);
			restart = 0;
		}
		printBoard(game.board, game.boardSize);
		getInput(command, 1024);
		selection=parseCommand(command, parsedCommand);
		switch (selection) {
		case 1:
			if (set(game, parsedCommand[1], parsedCommand[2], parsedCommand[3])) {
				winning = 1;
				break;
			}
		case 2:
			hint(&game, parsedCommand[1], parsedCommand[2]);
		case 3:
			validate(game);
		case 4:
			restart = 1;
		case 5:
			noexit = 1;
		case 6






	}
	



    srand(argc);


    int parsedCommand[4]={6};
    char command[1024];
    getInput(command, 1024);
    parseCommand(command,parsedCommand);
	while(parsedCommand[0]!
	return 0;
	
}
