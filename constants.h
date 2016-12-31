#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <windows.h>

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
/** MAX_CACHED_CHUNKS should be >= 4 or >= 9 (or even more) depending on the relaion betwen
 * chunk and display size.
 */
#define MAX_CACHED_CHUNKS 20

#define DISPLAY_SIZE_X 100
#define DISPLAY_SIZE_Y 40

#define MASK_UP 0b1000
#define MASK_DOWN 0b0100
#define MASK_LEFT 0b0010
#define MASK_RIGHT 0b0001

#define TICK_TIME_MS 10
#define GRAVITY -0.00000980665d

#define WALKING_SPEED 0.06d

enum material_type {AIR=0, DIRT, STONE};

typedef struct {
    double X;
    double Y;
} v2d;

typedef struct {
    int X;
    int Y;
} in2d;

typedef struct {
    enum material_type material;
    char id;
} block;

typedef struct {
    v2d pos;
    v2d speed;
    WORD collisions;
} player;

typedef struct {
    in2d offset;
    block data[CHUNK_SIZE_X][CHUNK_SIZE_Y];
    WINBOOL isloaded;
} chunk;


#endif // CONSTANTS_H_INCLUDED
