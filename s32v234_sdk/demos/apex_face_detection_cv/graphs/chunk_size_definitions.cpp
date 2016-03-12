

extern const int ACCUM_TILE_SIZE_X = 10;
extern const int ACCUM_TILE_SIZE_Y = 10;

extern const int VECT_TILE_SIZE_X = 8;// need to be redefined, otherwise g++ linker complains
extern const int VECT_TILE_SIZE_Y = 2;


extern const int BOX_64_WIDTH = ACCUM_TILE_SIZE_X;
extern const int BOX_64_HEIGHT = ACCUM_TILE_SIZE_Y;
extern const int BOX_64_AREA = BOX_64_WIDTH * BOX_64_HEIGHT;

extern const int BOX_SIZE = 5;
extern const int BOX_AREA = (2 * BOX_SIZE + 1) * (2 * BOX_SIZE + 1);
