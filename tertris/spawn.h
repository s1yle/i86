#ifndef SPAWN_H
#define SPAWN_H

#include "../cpu/types.h"

typedef struct Position {
	int x;
	int y;
} position;

/* Shape types */
typedef enum {
    SHAPE_I,
    SHAPE_J,
    SHAPE_L,
    SHAPE_O,
    SHAPE_S,
    SHAPE_T,
    SHAPE_Z,
    SHAPE_COUNT
} shape_type;

#define SHAPE_GRID_HEIGHT 4  // grid heigh (rows)
#define SHAPE_GRID_WIDTH 4   // grid with  (cols)

/* Shape structure */
typedef struct {
    shape_type type;
    int rotation;  /* 0-3 for 4 possible rotations */
    position pos;
} shape;

/* Function prototypes */
void spawn_item(shape_type t,position *p);
void rotate_shape(shape *s, int clockwise);
uint8_t get_width(shape_type t);

#endif
