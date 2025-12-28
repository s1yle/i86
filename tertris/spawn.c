#include "spawn.h"
#include "../drivers/screen.h"

/* Shape definitions - 4x4 grids for each shape type */
static const int shapes[SHAPE_COUNT][4][4] = {
    /* SHAPE_I */
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_J */
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_L */
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_O */
    {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_S */
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_T */
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_Z */
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

/* Rotation matrices for 90 degree rotations - placeholder for future implementation */
/* static const int rotation_matrices[4][4][4] = { ... }; */

void spawn_item(position *p) {
    /* Draw a T-shaped tetromino (more interesting than I shape) */
    shape s = create_shape(SHAPE_T, p->x, p->y);
    draw_shape(&s);

    shape s1 = create_shape(SHAPE_I, p->x+4, p->y);
    draw_shape(&s1);
     s1 = create_shape(SHAPE_J, p->x+5+4, p->y);
    draw_shape(&s1);
     s1 = create_shape(SHAPE_L, p->x+5+10, p->y);
    draw_shape(&s1);
     s1 = create_shape(SHAPE_O, p->x+5+16, p->y);
    draw_shape(&s1);
     s1 = create_shape(SHAPE_S, p->x+5+22, p->y);
    draw_shape(&s1);
     s1 = create_shape(SHAPE_Z, p->x+5+28, p->y);
    draw_shape(&s1);
}

void draw_square(position *p, int size) {
    char block[] = {'█', 0};  /* Create null-terminated string */
    char hash[] = "#";
    
    for(int i = 0 ; i < size; i++) {
        int horizontal = p->x + i;
        kprint_at(block, horizontal, p->y);
        kprint_at(block, horizontal, p->y + size - 1);
    }

    for(int i = 0 ; i < size; i++) {
        int vertical = p->y + i;
        kprint_at(hash, p->x, vertical);
        kprint_at(hash, p->x + size - 1, vertical);
    }
}

void draw_shape(shape *s) {
    char block[] = {'#', 0};  /* Create null-terminated string */
    const int (*shape_grid)[4] = shapes[s->type];
    
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (shape_grid[y][x]) {
                int screen_x = s->pos.x + x;
                int screen_y = s->pos.y + y;
                kprint_at(block, screen_x, screen_y);
            }
        }
    }
}

shape create_shape(shape_type type, int x, int y) {
    shape s;
    s.type = type;
    s.rotation = 0;
    s.pos.x = x;
    s.pos.y = y;
    return s;
}

void rotate_shape(shape *s, int clockwise) {
    if (clockwise) {
        s->rotation = (s->rotation + 1) % 4;
    } else {
        s->rotation = (s->rotation + 3) % 4;  /* +3 is same as -1 mod 4 */
    }
}

/* Helper function to get rotated shape cell */
int get_shape_cell(shape *s, int x, int y) {
    /* For now, return the base shape cell */
    /* TODO: Implement proper rotation using rotation matrices */
    return shapes[s->type][y][x];
}
