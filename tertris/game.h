#ifndef GAME_H
#define GAME_H
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"

extern int width_min;
extern int width_max;

void tertris_game_init();
void tertris_control(uint8_t scancode);
void tertris_game_exit();

#endif
