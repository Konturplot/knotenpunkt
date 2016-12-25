#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define WORLD_SIZE_X 128
#define WORLD_SIZE_Y 128

#define DISPLAY_SIZE_X 100
#define DISPLAY_SIZE_Y 40

enum material_type {AIR=0, DIRT, STONE};

typedef struct {
    enum material_type material;
} block;

#endif // CONSTANTS_H_INCLUDED
