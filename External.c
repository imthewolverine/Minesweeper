#include "External.h"

int Max(int n1,int n2){
   return n1 > n2 ? n1 : n2;
}

void ShowsCursor(bool visible){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = visible;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void SetPosition(short X, short Y){
    HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position= { X, Y };
    SetConsoleCursorPosition(Screen, Position);
}

void cPrint(short y, short x, char c){
    SetPosition(x,y);
    printf("%c",c);
}

void sPrint(short y,short x, char* s){
    SetPosition(x,y);
    printf("%s",s);
}

void Print(const Object object){
    cPrint(object.y,object.x,object.c);
}
