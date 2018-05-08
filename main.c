
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
/*const char * argv[]*/
int main(int argc) {
    srand(argc);
    int parsedCommand[4]={6};
    char command[1024];
    getInput(command, 1024);
    parseCommand(command,parsedCommand);
	
	return 0;
	
}
