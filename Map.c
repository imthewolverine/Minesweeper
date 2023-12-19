#include "Map.h"

static unsigned char ySize,xSize;
Cell* map;

void PrintMap(bool show){
    for (int i = 0; i < ySize*xSize; i++){
        if (!show || map[i].state == BombHit)
            PrintCell(map[i].object.y,map[i].object.x);
        else Print(map[i].object);
    }
}

void AssignDrawMap(signed char YSize, signed char XSize, signed char bombs){
    ySize = YSize; xSize = XSize;

    map = (Cell*)malloc(sizeof(Cell)*(ySize * xSize));
    for (int i = 0; i < ySize*xSize; i++) map[i].kind = EMPTY;
    //bomb bairluulah
    signed char randomY;
    signed char randomX;
    for (int i = 0; i<bombs;){
        randomY = rand() % ySize;
        randomX = rand() % xSize;

        if (GetCell(randomY,randomX)->kind != BOMB){
            GetCell(randomY,randomX)->kind = BOMB;
            GetCell(randomY,randomX)->object = (Object){'X',randomY,randomX};
            i++;
        }
    }
	/*hajuud bga bombiig tooloh*/
    Cell* cell;
    signed char n = 0;
    for (signed char y = 0; y < ySize; y++)
        for (signed char x = 0; x < xSize; x++){
            GetCell(y,x)->state = Closed;
            if (GetCell(y,x)->kind != BOMB){
                if (isCellBomb(y+1,x)) n++;
                if (isCellBomb(y,x+1)) n++;

                if (isCellBomb(y-1,x)) n++;
                if (isCellBomb(y,x-1)) n++;

                if (isCellBomb(y+1,x-1)) n++;
                if (isCellBomb(y-1,x+1)) n++;

                if (isCellBomb(y-1,x-1)) n++;
                if (isCellBomb(y+1,x+1)) n++;

                AssignCell(n,y,x);
                n = 0;
            }
        }
    PrintMap(false);
}

void OpenCells(signed char y, signed char x){
    if (GetCell(y,x)->kind != EMPTY) return;
    TryOpen(y+1,x);
    TryOpen(y,x+1);
    TryOpen(y-1,x);
    TryOpen(y,x-1);
    TryOpen(y+1,x-1);
    TryOpen(y-1,x+1);
    TryOpen(y-1,x-1);
    TryOpen(y+1,x+1);
}

void TryOpen(signed char y, signed char x){
    Cell *cell;
    if (!isOutside(y,x)) {
        cell = GetCell(y,x);
        if (cell->state == Open) return;
        cell->state = Open;

        PrintCell(y,x);
        if (cell->kind == EMPTY) OpenCells(y,x);
    }
}

void AssignCell(signed char n, signed char y, signed char x){
    Cell* cell = GetCell(y,x);
    switch (n){
        case 0: cell->kind = EMPTY; cell->object = (Object){' ',y,x}; break;
        case 1: cell->kind = ONE; cell->object = (Object){'1',y,x}; break;
        case 2: cell->kind = TWO; cell->object = (Object){'2',y,x}; break;
        case 3: cell->kind = THREE; cell->object = (Object){'3',y,x}; break;
        case 4: cell->kind = FOUR; cell->object = (Object){'4',y,x}; break;
        case 5: cell->kind = FIVE; cell->object = (Object){'5',y,x}; break;
        case 6: cell->kind = SIX; cell->object = (Object){'6',y,x}; break;
        case 7: cell->kind = SEVEN; cell->object = (Object){'7',y,x}; break;
        case 8: cell->kind = EIGHT; cell->object = (Object){'8',y,x}; break;
    }
}

Cell* GetCell(signed char y, signed char x){
    return &map[x+y * xSize];
}

bool isCellBomb(signed char y, signed char x){
    if (isOutside(y,x)) return false;
    return (GetCell(y,x)->kind == BOMB);
}

void Player(signed char bombs){
    Object player = (Object){'P',0,0};
    int tempy = 0,tempx = 0;
    bool gameover = false;
    bool showMap = false;
    short flagged = 0;
	signed char bombsFlagged = 0, questioned = 0;
	while (!gameover){
        switch (getch()){
            case 'w': if (!isOutside(player.y-1,player.x)) player.y--; break;
            case 's': if (!isOutside(player.y+1,player.x)) player.y++; break;
            case 'd': if (!isOutside(player.y,player.x+1)) player.x++; break;
            case 'a': if (!isOutside(player.y,player.x-1)) player.x--; break;
            case 'o': //open
                GetCell(player.y,player.x)->state = Open;
                OpenCells(player.y,player.x);
                if (GetCell(player.y,player.x)->kind == BOMB){
                    GetCell(player.y,player.x)->state = BombHit;
                    sPrint(ySize/2+1,10,"Game Over!");
                    gameover = true;
                }
                break;
            case 'f':// flag
                if (GetCell(player.y,player.x)->state == Open) break;
                if (GetCell(player.y,player.x)->state == Flagged){
                    flagged--;
                    GetCell(player.y,player.x)->state = Closed;
                    if (GetCell(player.y,player.x)->kind == BOMB) bombsFlagged--;
                    break;
                }
                flagged++;
                GetCell(player.y,player.x)->state = Flagged;
                if (GetCell(player.y,player.x)->kind == BOMB) bombsFlagged++;
                break;
            //garah
            case 'l': PrintMap(true); return;
        }
        if (bombsFlagged == bombs && flagged == bombs && questioned == 0){
            sPrint(ySize+2, 10," Game Won!");
            gameover = true;
        }
        showMap == false ? PrintCell(tempy,tempx) : Print(GetCell(tempy,tempx)->object);
        tempy = player.y; tempx = player.x;
        Print(player);
    }
    PrintMap(true);
}


void PrintCell(signed char y, signed char x){
   Object o = (Object){'#',y,x};
   switch (GetCell(y,x)->state){
        case BombHit: o = (Object){'X',y,x}; break;
        case Flagged: o = (Object){'F',y,x}; break;
        case Open: o = GetCell(y,x)->object; break;
        default: break;
   }
   Print(o);
}

bool isOutside(signed char y, signed char x){
   return (y < 0 || y >= ySize || x < 0 || x >= xSize);
}
