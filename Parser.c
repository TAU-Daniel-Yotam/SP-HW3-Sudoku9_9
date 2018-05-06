
#include "Parser.h"
#include "Game.h"
#include "Solver.h"
#include "MainAux.h"
#include <stdio.h>
#include <string.h>


int getInput(char* command, int size){
    if(fgets(command,size,stdin)==NULL){
        return 0;
    }
    return 1;
}

int * parseCommand(char*command, int* parsedCommand){
    char* word;
    int i=0;
    word=strtok(command," \t\r\n");
    while(word!=NULL){
        if(i==0){
            if(!strcmp(word,"set")){
                parsedCommand[i]=1;
            }
            else if(!strcmp(word,"hint")){
                parsedCommand[i]=2;
            }
            else if(!strcmp(word,"validate")){
                parsedCommand[i]=3;
            }
            else if(!strcmp(word,"restart")){
                parsedCommand[i]=4;
            }
            else if(!strcmp(word,"exit")){
                parsedCommand[i]=5;
            }
            else{
                parsedCommand[i]=6;
                break;
            }
        }
        else{
            parsedCommand[i] =parseInt(word, parseSize(word));
            
        }
        i++;
        word=strtok(NULL," \t\r\n");
        
    }
    return parsedCommand;
}

int parseSize(char * word){
    int i=0;
    while(word[i]!='\0'){
        i++;
    }
    return i;
    
}

int parseInt(char* str, int size){
    int result=0;
    int pow=1;
    int i;
    for(i=size-1; i>=0; i--){
        result += pow*(str[i]-48);
        pow*=10;
    }
    return result;
}
