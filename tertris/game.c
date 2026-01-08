#include "game.h"
#include "../cpu/timer.h"
#include "../libc/xorshift32.h"
#include "../libc/mem.h"
#include "test.h"


int width_min = MAX_COLS/4;
int width_max = (MAX_COLS/2*1.5);

static game_data_t gd = { .manipulate_item = NULL };
void tertris_draw_border();
static uint32_t rand_val = 0;
static uint8_t tick = 0;

void tertris_game_init() {
	// disable keyboard
	KEYBOARD_TERTRIS = 0x01;

	// setting border and game region
	clear_screen();
	tertris_draw_border();
	rand_val = prng_next();

	add_timer(1, tertris_game_update, 1);
	// test_spawn_item();
}
#define game_update true
#ifdef game_update
static int i = 1;
void tertris_game_update() {
	tick++;

	if(tick >= 50) {
		// game update on every tick
		rand_val = prng_next();
		char str[16]; int_to_ascii(rand_val, str);
		kprint_at(str,0,0);

		if(gd.manipulate_item != NULL) {
			// already spawned

			kprint_at("0x000000",0,1);

		} else if (gd.manipulate_item == NULL) {
			// havnt spawned yet

			position p; 
			p.x = prng_next_mod(width_min, width_max);
			p.y = 0;

			uint8_t sindex = prng_next_mod(0, SHAPE_COUNT);
			// allocate memory for the new shape
			gd.manipulate_item = (shape *)kmalloc(sizeof(shape), 0, NULL);
			spawn_item((shape_type)sindex, &p, gd.manipulate_item);

			char str2[16]; int_to_ascii(p.x, str2);
			kprint_at(str2,0,0);

			i++;
		}

		tick = 0;
	}
}
#else
#endif


// A S D  for moving the item
// space for rotating 
void tertris_control(uint8_t scancode) {
	if(gd.manipulate_item != NULL) {

	}
}

void tertris_spawn() {
	
}

void tertris_draw_border() {
	int row;
	int col;

	for (row = 0; row <= MAX_ROWS - 1;) {
		for(col = width_min; col <= width_max - 1; col += 1) {

			if(row == MAX_ROWS - 1) {
				// char* msg;
				// int_to_ascii(row, msg);
				kprint_at("#", col, row);
			} 
			else if(col == width_min || col == width_max - 1) {
				// char* msg_row;
				// int_to_ascii(row, msg_row);
				// char* msg;
				// int_to_ascii(col, msg);
				kprint_at("#", col, row);
			}

			if(col == width_max - 1) {
				row += 1;
			}
	
		}
	}

}





void tertris_game_exit() {
	KEYBOARD_TERTRIS = 0x01;

	clear_screen();
}
