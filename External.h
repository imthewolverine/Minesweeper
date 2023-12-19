#ifndef EXTERNAL_H_INCLUDED
#define EXTERNAL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
typedef struct Object{
    char c;
    short y,x;
}Object;

int Max(int n1,int n2);
void ShowsCursor(bool visible);
void SetPosition(short X, short Y);
void cPrint(short y, short x, char c);
void sPrint(short y,short x, char* s);
void Print(const Object object);

#endif
