#include <stdlib.h>

#include <windows.h>

#include "constants.h"


extern block world[WORLD_SIZE_X][WORLD_SIZE_Y];
extern player self;

extern HANDLE hDisplayConsole;

WINBOOL clear_console(HANDLE hConsole)
{
    COORD coordinates;
    DWORD numwr = 0;
    CONSOLE_SCREEN_BUFFER_INFO cbi;

    coordinates.X = 0;
    coordinates.Y = 0;

    if(!GetConsoleScreenBufferInfo(hDisplayConsole, &cbi)) {
        return FALSE;
    }

    if(!FillConsoleOutputAttribute(hDisplayConsole,
                                   FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED,
                                   (DWORD) cbi.dwSize.X * cbi.dwSize.Y,
                                   coordinates,
                                   &numwr)) {
        return FALSE;
    }

    if(!FillConsoleOutputCharacter(hDisplayConsole, ' ',
                                   (DWORD) cbi.dwSize.X * cbi.dwSize.Y,
                                   coordinates,
                                   &numwr)) {
        return FALSE;
    }

    return TRUE;
}


void draw_world(int x, int y)
{
    char constr[DISPLAY_SIZE_X * DISPLAY_SIZE_Y ];
    WORD conattrs[DISPLAY_SIZE_X * DISPLAY_SIZE_Y];

    COORD coordinates;
    DWORD numwr = 0;

    const WORD attrs_green = FOREGROUND_GREEN;
    const WORD attrs_def = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;

    coordinates.X = 0;
    coordinates.Y = 0;

    for(int i = 0; i < DISPLAY_SIZE_Y; i++) {
        for(int n = 0; n < DISPLAY_SIZE_X; n++) {
            int world_x = x + n - (DISPLAY_SIZE_X / 2);
            int world_y = y - i + (DISPLAY_SIZE_Y / 2);

            if((world_x < 0) || (world_y < 0)) {
                continue;
            }

            /*coordinates.X = i;
            coordinates.Y = n;*/

            switch (world[world_x][world_y].material) {
            case DIRT:
                conattrs[n + (i * DISPLAY_SIZE_X)] = attrs_green;
                constr[n + (i * DISPLAY_SIZE_X)] = '#';
                break;

            case STONE:
                conattrs[n + (i * DISPLAY_SIZE_X)] = attrs_def;
                constr[n + (i * DISPLAY_SIZE_X)] = '%';
                break;

            default:
                conattrs[n + (i * DISPLAY_SIZE_X)] = attrs_def;
                constr[n + (i * DISPLAY_SIZE_X)] = ' ';
                break;
            }
        }
    }

    coordinates.X = 0;
    coordinates.Y = 0;

    WriteConsoleOutputAttribute(hDisplayConsole,
                                conattrs, DISPLAY_SIZE_X * DISPLAY_SIZE_Y, coordinates, &numwr);
    WriteConsoleOutputCharacter(hDisplayConsole, constr,
                                DISPLAY_SIZE_X * DISPLAY_SIZE_Y, coordinates, &numwr);

    coordinates.X = self.pos.X - x + (DISPLAY_SIZE_X / 2);
    coordinates.Y = self.pos.Y - y + (DISPLAY_SIZE_Y / 2);
    WriteConsoleOutputAttribute(hDisplayConsole, &attrs_def, 1, coordinates,
                                &numwr);
    WriteConsoleOutputCharacter(hDisplayConsole, "@", 1, coordinates, &numwr);
}
