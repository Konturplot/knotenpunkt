#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <windows.h>

#include "constants.h"
#include "worldutils.h"

chunk cache[MAX_CACHED_CHUNKS];

block getworldblock(int x, int y)
{
    in2d worldcoord;
    worldcoord.X = x;
    worldcoord.Y = y;
    in2d offset = getchunkoffset(worldcoord);

    worldcoord = world2chunk(worldcoord);
    return getcachechunk(offset)->data[worldcoord.X][worldcoord.Y];
}

chunk* getcachechunk(in2d offset)
{
    static unsigned short numcached;

    for(int i=0; i < numcached; i++) {
        if((cache[i].offset.X == offset.X) && (cache[i].offset.Y == offset.Y)) {
            return &cache[i];
        }
    }

    if(numcached < MAX_CACHED_CHUNKS) {
        loadchunk(&cache[numcached], offset);
        numcached++;
        return &cache[numcached - 1];
    } else {
        unloadchunk(&cache[0]);
        for(int i=0; i < (MAX_CACHED_CHUNKS - 1); i++) {
            cache[i] = cache[i + 1];
        }
        loadchunk(&cache[MAX_CACHED_CHUNKS - 1], offset);
        return &cache[MAX_CACHED_CHUNKS - 1];
    }
}

void loadchunk(chunk* toload, in2d offset)
{
    toload->offset = offset;
    /* TODO (Simon#1#): try to load chunk from file and only generate otherwise*/

    for(int i=0; i < CHUNK_SIZE_Y; i++) {
        for(int n=0; n < CHUNK_SIZE_X; n++) {
            in2d chunkcoord;
            chunkcoord.X = n;
            chunkcoord.Y = i;

            toload->data[chunkcoord.X][chunkcoord.Y] = genworldblock(chunk2world(chunkcoord,
                    offset));
        }
    }
}

void unloadchunk(chunk* tounload)
{
    /* TODO (Simon#1#): make sure the chunk is saved */
    return;
}

in2d world2chunk(in2d worldcoord)
{
    in2d toret;

    toret.X = worldcoord.X % CHUNK_SIZE_X;
    toret.Y = worldcoord.Y % CHUNK_SIZE_Y;

    if(toret.X < 0) {
        toret.X = toret.X + CHUNK_SIZE_X;
    }

    if(toret.Y < 0) {
        toret.Y = toret.Y + CHUNK_SIZE_Y;
    }

    return toret;
}

in2d getchunkoffset(in2d worldcoord)
{
    in2d toret;

    toret.X = worldcoord.X / CHUNK_SIZE_X;
    toret.Y = worldcoord.Y / CHUNK_SIZE_Y;

    if(worldcoord.X < 0) {
        if(worldcoord.X % CHUNK_SIZE_X) {
            toret.X--;
        }
    }

    if(worldcoord.Y < 0) {
        if(worldcoord.Y % CHUNK_SIZE_Y) {
            toret.Y--;
        }
    }

    return toret;
}

in2d chunk2world(in2d chunkcoord, in2d chunkoffset)
{
    in2d toret;

    toret.X = chunkcoord.X + (CHUNK_SIZE_X * chunkoffset.X);
    toret.Y = chunkcoord.Y + (CHUNK_SIZE_Y * chunkoffset.Y);

    return toret;
}

block genworldblock(in2d worldcoord)
{
    block toret;

    if(worldcoord.Y < 64) {
        toret.material = STONE;
        toret.id = '%';
    } else if(worldcoord.Y == 64) {
        toret.material = DIRT;
        toret.id = '#';
    } else if(worldcoord.Y == 65) {
        if(worldcoord.X  % 2) {
            toret.material = DIRT;
            toret.id = '#';
        } else {
            toret.material = AIR;
            toret.id = ' ';
        }
    } else {
        toret.material = AIR;
        toret.id = ' ';
    }

    return toret;
}

