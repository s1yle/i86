#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>
#include "../tertris/game.h"
#include "../libc/xorshift32.h"

static uint32_t rand_seed = 20060426;

void kernel_main() {
    isr_install();
    irq_install();

    __asm__("int $2");
    __asm__("int $3");

    kprint("Type something, it will go through the kernel\n"
        "Type END to halt the CPU or PAGE to request a kmalloc()\n> ");

    prng_seed(rand_seed);
    //tertris_game_init();
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        __asm__ __volatile__("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
        /* Lesson 22: Code to test kmalloc, the rest is unchanged */
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    } else if (strcmp(input, "TERTRIS") == 0) {
        tertris_game_init();
    }

    /*
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
    */
}
