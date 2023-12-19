#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "External.h"

typedef enum CellState{
    Flagged, Open, Closed, WrongBomb, BombHit
}CellState;

typedef enum CellKind{
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, BOMB, EMPTY
}CellKind;

typedef struct Cell{
    Object object;
    CellKind kind;
    CellState state;
}Cell;

void PrintMap(bool show);
void AssignDrawMap(signed char XSize, signed char YSize, signed char bombs);
Cell* GetCell(signed char y, signed char x);
void Player(signed char bombs);
bool isOutside(signed char y, signed char x);
bool isCellBomb(signed char y, signed char x);
void AssignCell(signed char n, signed char y, signed char x);
void OpenCells(signed char y, signed char x);
void TryOpen(signed char y, signed char x);
void PrintCell(signed char y, signed char x);
#endif
