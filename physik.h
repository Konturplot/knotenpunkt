#ifndef PHYSIK_H_INCLUDED
#define PHYSIK_H_INCLUDED

#include <windows.h>

#include "constants.h"

/** \brief Calculates the kinetics
 *
 * \param void
 * \return void
 *
 */
void apply_physics(void);

/** \brief Sets all the initial attributes for a player.
 *
 * \param pl player
 * \return void
 *
 */
void init_player(player* pl);


/** \brief Accelerates the player
 *
 * \param pl player* Pointer to the player to be accelerated
 * \param acceleration float Value of the acceleration
 * \return void
 *
 */
void accel_player(player* pl, v2d acceleration);

/** \brief Moves the player according to its speed
 *
 * \param pl player* The player to move
 * \return void
 *
 */
void move_player(player* pl);

#endif // PHYSIK_H_INCLUDED
