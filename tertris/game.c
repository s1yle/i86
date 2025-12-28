#include "game.h"
#include "spawn.h"
void tertris_game_init() {
	// disable keyboard
	KEYBOARD_TERTRIS = 0x01;

	// setting border and game region
	clear_screen();
	tertris_draw_border();	

	position p = { 10, 10 };
	spawn_item(&p);
}


void tertris_draw_border() {
	int row;
	int col;
	for (row = 0; row <= MAX_ROWS - 1;) {
		for(col = 0; col <= MAX_COLS - 1; col += 1) {

			if(row == MAX_ROWS - 1) {
				char* msg;
				int_to_ascii(row, msg);
				kprint_at("#", col, row);
			} 
			else if( (col == 0 || col == MAX_COLS - 1)) {
				char* msg_row;
				int_to_ascii(row, msg_row);
				char* msg;
				int_to_ascii(col, msg);
				kprint_at(msg_row, col, row);
			}

			if(col == MAX_COLS - 1) {
				row += 1;
			}
	
		}
	}

}


void tertris_control(uint8_t scancode) {

}



void tertris_game_exit() {
	KEYBOARD_TERTRIS = 0x01;

	clear_screen();
}
