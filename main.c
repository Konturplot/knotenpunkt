#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <windows.h>

#include "zim_con.h"

#include "constants.h"
#include "drawer.h"
#include "physik.h"



/*          X             Y     */
block world[WORLD_SIZE_X][WORLD_SIZE_Y];

player self;

HANDLE hDisplayConsole;
SMALL_RECT windowrect;

void at_exit(void)
{
    SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
}

int main()
{
    FILETIME last_time, this_time;
    LONGLONG thistime, lasttime;

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

    CONSOLE_CURSOR_INFO cursorinf;
    GetConsoleCursorInfo(hDisplayConsole, &cursorinf);
    cursorinf.bVisible = FALSE;
    SetConsoleCursorInfo(hDisplayConsole, &cursorinf);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorinf);

    SetConsoleActiveScreenBuffer(hDisplayConsole);

    system("MODE CON COLS=100 LINES=40");

    mdebug("Done.");

    draw_world(64, 64);

    init_player(&self);

    draw_world(self.pos.X, self.pos.Y);

    mlog("Entering main loop.");
    /*main loop*/
    while(!GetAsyncKeyState(VK_ESCAPE)) {
        GetSystemTimeAsFileTime(&last_time);

        /*TODO calculate physics and move the player accordingly*/
        /*TODO get the elapsed time during calculation and sleep shorter than
        50 milliseconds so that the actual updating frequenca is closer to 20Hz*/
        apply_physics();

        GetSystemTimeAsFileTime(&this_time);

        /* Calculate tick time */
        thistime = ((LONGLONG)this_time.dwHighDateTime << 32LL) +
                   (LONGLONG)this_time.dwLowDateTime;
        lasttime = ((LONGLONG)last_time.dwHighDateTime << 32LL) +
                   (LONGLONG)last_time.dwLowDateTime;

        if((thistime - lasttime) > 10000 * TICK_TIME_MS) {
            merror("Ticked: %fms", (thistime - lasttime)/10000.0f);
            merror("Single tick was longer than %ims!", TICK_TIME_MS);
            exit(1);
        }
        mdebug("Ticked: %fms", (thistime - lasttime)/10000.0f);

        SleepEx(TICK_TIME_MS, FALSE);
    }

    /*Need to clear the stdin buffer so the "Press any key to continue" stays*/
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    return 0;
}
