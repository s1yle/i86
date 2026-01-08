#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../cpu/types.h"

extern uint8_t KEYBOARD_TERTRIS;

void init_keyboard();
char get_letter(char scancode);
void print_keyboard(char scancode, int col, int row);

#endif
