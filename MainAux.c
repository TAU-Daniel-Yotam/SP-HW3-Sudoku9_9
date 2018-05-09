

#include "MainAux.h"
#include <stdlib.h>

int getRandomInt(int bound){
    return 1+rand()%bound;
}

int calcSizeOfArray(int*a){
    return sizeof(a)/ sizeof(int);
}