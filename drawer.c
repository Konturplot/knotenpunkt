#include <stdlib.h>

#include <windows.h>

#include "constants.h"


extern block world[WORLD_SIZE_X][WORLD_SIZE_Y];

extern HANDLE hDisplayConsole;

void draw_world(int x, int y) {
    _COORD coordinates;

    coordinates.X = x;
    coordinates.Y = y;

    system("cls");

    WriteConsoleOutputCharacter(hConsole, char, 1, coordinates, NULL);
}
