#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define WORLD_SIZE_X 128
#define WORLD_SIZE_Y 128

enum material_type {AIR=0, DIRT, STONE};

typedef struct {
    enum material_type material;
} block;

#endif // CONSTANTS_H_INCLUDED
