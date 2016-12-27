#include <windows.h>

#include "constants.h"
#include "drawer.h"
#include "physik.h"

extern player self;
extern block world[WORLD_SIZE_X][WORLD_SIZE_Y];

/** Timebase for all functions is milliseconds
 * distance base is "blocks" a unit of one character
 * therefore a point is blocks, speed is blocks/milliescond
 * and acceleration is blocks/millisecond�
 *
 */
void apply_physics(void)
{
    /** Apply gravity if the player isn't colloded downwards#
     *
     */
    if(!(self.collisions & MASK_DOWN)) {
        if(!move_player(&self)) {
            v2d gravity;
            gravity.X = 0.0d;
            gravity.Y = GRAVITY;
            accel_player(&self, gravity);
        } else {
            self.speed.X = 0.0d;
            self.speed.Y = 0.0d;
            self.collisions = self.collisions | MASK_DOWN;
        }
    }

    draw_world(self.pos.X, self.pos.Y);
}

/** TODO (Simon#1#): Make a spawnpoint and automatically set
 * the players coordinates there wen initializing.
 * Necessary to properly "spawn" a player.
 *
 */
void init_player(player* pl)
{
    pl->pos.X = 64;
    pl->pos.Y = 100;
    pl->collisions = 0b0000;
}

/** This function must be run every tick (20 times per second)
 * to be accurate. Just as all kinetic calculations
 */
void accel_player(player* pl, v2d acceleration)
{
    pl->speed.X = pl->speed.X + (acceleration.X * (double) TICK_TIME_MS);
    pl->speed.Y = pl->speed.Y + (acceleration.Y * (double) TICK_TIME_MS);
}

WINBOOL move_player(player* pl)
{
    pl->pos.X = pl->pos.X + (pl->speed.X * 0.5d * (double) TICK_TIME_MS);
    pl->pos.Y = pl->pos.Y + (pl->speed.Y * 0.5d * (double) TICK_TIME_MS);

    if(pl->pos.X < 0 || pl->pos.Y < 0 || pl->pos.X >= WORLD_SIZE_X
            || pl->pos.Y >= WORLD_SIZE_Y) {
        return FALSE;
    }

    if(world[(int) (pl->pos.X)][(int) (pl->pos.Y - 1)].material == AIR) {
        return FALSE;
    } else {
        return TRUE;
    }
}