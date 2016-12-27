#ifndef DRAWER_H_INCLUDED
#define DRAWER_H_INCLUDED

#include <windows.h>

/** \brief Clears a Console defined by its handle
 *
 * \param hConsole The handle to the console you want to clear
 * \return TRUE for success, FALSE otherwise
 *
 */
WINBOOL clear_console(HANDLE hConsole);

/** \brief Draws the World wogether with the player
 *
 * \param x int Viewport center X coordinate
 * \param y int Viewport center Y coordinate
 * \return void
 *
 */
void draw_world(int x, int y);

#endif // DRAWER_H_INCLUDED
