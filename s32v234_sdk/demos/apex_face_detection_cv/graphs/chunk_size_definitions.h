#ifndef CHUNK_SIZE_DEFINITIONS_H
#define CHUNK_SIZE_DEFINITIONS_H

#ifdef APEX2_EMULATE
extern const int ACCUM_TILE_SIZE_X;
extern const int ACCUM_TILE_SIZE_Y;
#else
const int ACCUM_TILE_SIZE_X = 10; // otherwise g++ linker complains
const int ACCUM_TILE_SIZE_Y = 10;
#endif



#ifdef APEX2_EMULATE
extern const int VECT_TILE_SIZE_X;// need to be redefined, otherwise g++ linker complains
extern const int VECT_TILE_SIZE_Y;
#else
const int VECT_TILE_SIZE_X = 1;// need to be redefined, otherwise g++ linker complains
const int VECT_TILE_SIZE_Y = 1;
#endif

#endif