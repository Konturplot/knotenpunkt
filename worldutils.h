#ifndef WORLDUTILS_H_INCLUDED
#define WORLDUTILS_H_INCLUDED

#include "constants.h"

block getworldblock(int x, int y);

chunk* getcachechunk(in2d offset);

chunk* kot(in2d o);

void loadchunk(chunk* toload, in2d offset);

void unloadchunk(chunk* tounload);

in2d world2chunk(in2d worldcoord);

in2d getchunkoffset(in2d worldcoord);

in2d chunk2world(in2d chunkcoord, in2d chunkoffset);

block genworldblock(in2d worldcoord);

#endif // WORLDUTILS_H_INCLUDED
