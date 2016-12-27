#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <windows.h>

#define WORLD_SIZE_X 128
#define WORLD_SIZE_Y 128

#define DISPLAY_SIZE_X 100
#define DISPLAY_SIZE_Y 40

#define MASK_UP 0b1000
#define MASK_DOWN 0b0100
#define MASK_LEFT 0b0010
#define MASK_RIGHT 0b0001

#define TICK_TIME_MS 5
#define GRAVITY -0.00000980665d

enum material_type {AIR=0, DIRT, STONE};

typedef struct {
    double X;
    double Y;
} v2d;

typedef struct {
    enum material_type material;
} block;

typedef struct {
    v2d pos;
    v2d speed;
    WORD collisions;
} player;


#endif // CONSTANTS_H_INCLUDED
