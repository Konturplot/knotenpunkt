#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <windows.h>

#include "zim_con.h"

#include "constants.h"
#include "drawer.h"
#include "physik.h"
#include "worldutils.h"

player self;

HANDLE hDisplayConsole;
SMALL_RECT windowrect;


void at_exit(void)
{
    SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
#ifdef RELEASE
    system("pause");
#endif // RELEASE
}

int main()
{
    FILETIME last_time, this_time;
    LONGLONG thistime, lasttime;

    mlog("Starting...");

    mdebug("Setting atexit() routine...");
    atexit((void*) at_exit);
    mdebug("Done...");

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

        apply_physics();

        GetSystemTimeAsFileTime(&this_time);

        /* Calculate tick time */
        thistime = ((LONGLONG)this_time.dwHighDateTime << 32LL) +
                   (LONGLONG)this_time.dwLowDateTime;
        lasttime = ((LONGLONG)last_time.dwHighDateTime << 32LL) +
                   (LONGLONG)last_time.dwLowDateTime;

        if((thistime - lasttime) > (10000 * TICK_TIME_MS)) {
            merror("Ticked: %fms", ((double)(thistime - lasttime))/10000.0d);
            merror("Single tick was longer than %ims!", TICK_TIME_MS);
            exit(-123);
        }
        mdebug("Ticked: %fms", ((double)(thistime - lasttime))/10000.0d);

        SleepEx(TICK_TIME_MS - ((thistime - lasttime)/10000), FALSE);
    }

    /*Need to clear the stdin buffer so the "Press any key to continue" stays*/
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    return 0;
}
