#include <stdlib.h>

#include <windows.h>

#include "constants.h"


extern block world[WORLD_SIZE_X][WORLD_SIZE_Y];

extern HANDLE hDisplayConsole;

void draw_world(int x, int y)
{
    COORD coordinates;
    DWORD numwr = 0;

    const WORD attrs_green = FOREGROUND_GREEN;

    system("cls");

    for(int i = 0; i < DISPLAY_SIZE_X; i++) {
        for(int n = 0; n < DISPLAY_SIZE_Y; n++) {
            int world_x = x + i - (DISPLAY_SIZE_X / 2);
            int world_y = y - n + (DISPLAY_SIZE_Y / 2);

            if((world_x < 0) || (world_y < 0)) {
                continue;
            }

            coordinates.X = i;
            coordinates.Y = n;

            switch (world[world_x][world_y].material) {
            case DIRT:
                WriteConsoleOutputAttribute(hDisplayConsole,
                                            &attrs_green, 1, coordinates, &numwr);
                WriteConsoleOutputCharacter(hDisplayConsole, "#", 1, coordinates, &numwr);
                break;

            case STONE:
                WriteConsoleOutputCharacter(hDisplayConsole, "%", 1, coordinates, &numwr);
                break;

            default:
                break;
            }
        }
    }
}
