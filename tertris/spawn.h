#ifndef SPAWN_H
#define SPAWN_H

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

/* Shape structure */
typedef struct {
    shape_type type;
    int rotation;  /* 0-3 for 4 possible rotations */
    position pos;
} shape;

/* Function prototypes */
void spawn_item(position *p);
void draw_square(position *p, int size);
void draw_shape(shape *s);
shape create_shape(shape_type type, int x, int y);
void rotate_shape(shape *s, int clockwise);

#endif
