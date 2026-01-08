#ifndef GAME_H
#define GAME_H
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "spawn.h"

#define TESTGAME 1
#define SPAWN_INTERVAL 50
#define FALL_INTERVAL 30

extern int width_min;
extern int width_max;
extern int border_height;

#define TERTRIS_EXPIRE_TICK 50

typedef struct game_data
{
    shape *manipulate_item;
    shape *fixed_item[25][80];
} game_data_t;

extern game_data_t gd;

void tertris_game_init();
void tertris_control(uint8_t scancode);
void tertris_game_exit();
void tertris_game_update();

// manipulate the shape
void move_shape(shape*s, int dx, int dy);
void rotate_shape_clockwise(shape *s);
void fix_current_shape();

#endif
