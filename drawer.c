#include <stdlib.h>

#include <windows.h>

#include "worldutils.h"
#include "constants.h"

extern player self;

extern HANDLE hDisplayConsole;

POINT point;
RECT consolewindoerect;

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
    const WORD attrs_player = FOREGROUND_BLUE|BACKGROUND_RED
                              |BACKGROUND_GREEN|BACKGROUND_BLUE
                              |BACKGROUND_INTENSITY;
    const WORD attrs_highlight = BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE
                              |BACKGROUND_INTENSITY;
    const WORD attrs_def = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;

    /* clear_console(hDisplayConsole); */

    coordinates.X = 0;
    coordinates.Y = 0;

    for(int i = 0; i < DISPLAY_SIZE_Y; i++) {
        for(int n = 0; n < DISPLAY_SIZE_X; n++) {
            int world_x = x + n - (DISPLAY_SIZE_X / 2);
            int world_y = y - i + (DISPLAY_SIZE_Y / 2);

            block worldblock = getworldblock(world_x, world_y);
            switch (worldblock.material) {
            case DIRT:
                conattrs[n + (i * DISPLAY_SIZE_X)] = attrs_green;
                break;

            case STONE:
                conattrs[n + (i * DISPLAY_SIZE_X)] = attrs_def;
                break;

            default:
                conattrs[n + (i * DISPLAY_SIZE_X)] = attrs_def;
                break;
            }
            constr[n + (i * DISPLAY_SIZE_X)] = worldblock.id;
        }
    }

    /*highlight the mouse position*/
    GetCursorPos(&point);
    GetClientRect(GetConsoleWindow(), &consolewindoerect);
    MapWindowPoints(GetConsoleWindow(), NULL, &consolewindoerect, 2);

    if((point.y >= consolewindoerect.top) && (point.y <= consolewindoerect.bottom)
            && (point.x >= consolewindoerect.left)
            && (point.x <= consolewindoerect.right)) {
        conattrs[(int)((point.x - consolewindoerect.left) * ((float)DISPLAY_SIZE_X /
                 (consolewindoerect.right - consolewindoerect.left)) + ((int)((
                             point.y - consolewindoerect.top) * ((float)DISPLAY_SIZE_Y / (consolewindoerect.bottom -
                                     consolewindoerect.top))) * DISPLAY_SIZE_X))] = attrs_highlight;
    }

    /*put the player*/
    conattrs[((int)self.pos.X - x + DISPLAY_SIZE_X / 2) + (((
                 int)self.pos.Y - y + DISPLAY_SIZE_Y / 2) * DISPLAY_SIZE_X)] = attrs_player;
    constr[((int)self.pos.X - x + DISPLAY_SIZE_X / 2) + (((int)self.pos.Y - y +
            DISPLAY_SIZE_Y / 2) * DISPLAY_SIZE_X)] = '@';

    /*Draw everything*/
    WriteConsoleOutputAttribute(hDisplayConsole,
                                conattrs, DISPLAY_SIZE_X * DISPLAY_SIZE_Y, coordinates, &numwr);
    WriteConsoleOutputCharacter(hDisplayConsole, constr,
                                DISPLAY_SIZE_X * DISPLAY_SIZE_Y, coordinates, &numwr);
}
