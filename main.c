
#include <stdio.h>
#include "Parser.h"
/*int argc, const char * argv[]*/
int main() {
    int parsedCommand[4]={6};
    char command[1024];
    getInput(command, 1024);
    parseCommand(command,parsedCommand);
	
	return 0;
	
}
