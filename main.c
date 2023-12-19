#include <stdio.h>
#include <stdlib.h>
#include "External.h"
#include "Map.h"
#include <time.h>
#include <conio.h>

extern Cell* map;

int main(){
    srand(time(NULL));
    ShowsCursor(false);
    int ylength = 9, xlength = 9, bombs = 10;
    system("cls");
    AssignDrawMap(ylength,xlength,bombs);
    Player(bombs);
    free(map);
    map = NULL;

    sPrint(ylength+5,Max(xlength/2 - 10,0),"Thanks for playing!");
    return 0;
}
