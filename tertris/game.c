#include "game.h"
#include "spawn.h"

int width_min = MAX_COLS/4;
int width_max = (MAX_COLS/2*1.5);

/* Function prototype */
void tertris_draw_border();

void tertris_game_init() {
	// disable keyboard
	KEYBOARD_TERTRIS = 0x01;

	// setting border and game region
	clear_screen();
	tertris_draw_border();	
}

void test_spawn_item() {
	/* 测试边界检测功能 */
	position p1 = { 110, 0 };
	spawn_item(SHAPE_O, &p1);
	
	position p2 = { 110, 4 };
	spawn_item(SHAPE_T, &p2);

	position pp2 = { 110, 8 };
	spawn_item(SHAPE_I, &pp2);
	
	position pp3 = { 110, 12 };
	spawn_item(SHAPE_J, &pp3);
	
	position p3 = { 110, 16 };
	spawn_item(SHAPE_L, &p3);
	
	position p4 = { 110, 20 };
	spawn_item(SHAPE_Z, &p4);

	position p5 = { 110, 24 };
	spawn_item(SHAPE_S, &p5);

	
	/* 测试边界检测功能 */
	position o1 = { 0, 0 };
	spawn_item(SHAPE_O, &o1);
	
	position o2 = { 0, 4 };
	spawn_item(SHAPE_T, &o2);

	position o3 = { 0, 8 };
	spawn_item(SHAPE_I, &o3);
	
	position o4 = { 0, 12 };
	spawn_item(SHAPE_J, &o4);
	
	position o5 = { 0, 16 };
	spawn_item(SHAPE_L, &o5);
	
	position o6 = { 0, 20 };
	spawn_item(SHAPE_Z, &o6);

	position o7 = { 0, 24 };
	spawn_item(SHAPE_S, &o7);
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


void tertris_control(uint8_t scancode) {

}



void tertris_game_exit() {
	KEYBOARD_TERTRIS = 0x01;

	clear_screen();
}
