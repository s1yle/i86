#ifndef GAME_H
#define GAME_H
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "spawn.h"

extern int width_min;
extern int width_max;

#define TERTRIS_EXPIRE_TICK 50

typedef struct game_data
{
    shape *manipulate_item;
    shape *fixed_item[25][50];
} game_data_t;


void tertris_game_init();
void tertris_control(uint8_t scancode);
void tertris_game_exit();
void tertris_game_update();

#endif
