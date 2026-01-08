#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"
#include <stdint.h>
#include "../tertris/game.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

uint8_t KEYBOARD_TERTRIS = 0x00;
static char key_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

void print_keyboard(char scancode, int col, int row) {
	if(scancode > SC_MAX) return;

	char letter = get_letter(scancode);
	char str[2] = {letter, '\0'};

	if(col >= 0 && row >= 0) {
		kprint_at(str, col, row);
	} else {
		kprint_at(str,0,2);
	}
}

static void keyboard_callback(registers_t *regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);
    
	if (scancode > SC_MAX) return;
	if (KEYBOARD_TERTRIS == 0x01) {
		tertris_control(scancode);
		return;
	}

	if (scancode == BACKSPACE) {
		backspace(key_buffer);
		kprint_backspace();
	} else if (scancode == ENTER) {
		kprint("\n");
		user_input(key_buffer); /* kernel-controlled function */
		key_buffer[0] = '\0';
	} else {
		char letter = sc_ascii[(int)scancode];
		/* Remember that kprint only accepts char[] */
		char str[2] = {letter, '\0'};
		append(key_buffer, letter);
		kprint(str);
	}
	UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

char get_letter(char scancode) {
	if (scancode > SC_MAX) return '?';
	return sc_ascii[(int)(scancode)];
}