#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <windows.h>

#include "zim_con.h"
#include "constants.h"



/*          X             Y     */
block world[WORLD_SIZE_X][WORLD_SIZE_Y];

HANDLE hDisplayConsole;
SMALL_RECT windowrect;

void at_exit(void)
{
    SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
}

int main()
{
    mlog("Starting...");

    mdebug("Setting atexit() routine...");
    atexit((void*) at_exit);
    mdebug("Done...");

    mlog("Generating world...");

    for(int i = 0; i < WORLD_SIZE_X; i++) {
        /*one layer of dirt*/
        world[i][WORLD_SIZE_Y / 2].material = DIRT;

        /*below that stone*/
        for(int n = 0; n < WORLD_SIZE_Y / 2; n++) {
            world[i][n].material = STONE;
        }
    }

    mdebug("Done.");

    mlog("Setting up output...");

    hDisplayConsole = CreateConsoleScreenBuffer(
                          GENERIC_READ | GENERIC_WRITE,
                          FILE_SHARE_READ |
                          FILE_SHARE_WRITE,        // shared
                          NULL,                    // default security attributes
                          CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
                          NULL);

    windowrect.Left = 0;
    windowrect.Top = 0;
    windowrect.Right = 100;
    windowrect.Bottom = 40;

    SetConsoleWindowInfo(hDisplayConsole, TRUE, &windowrect);

    SetConsoleActiveScreenBuffer(hDisplayConsole);

    system("MODE CON COLS=100 LINES=40");

    mdebug("Done.");

    draw_world(0, 0);

    return 0;
}
