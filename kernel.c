#include <stddef.h>
#include <stdint.h>

#include "vga.h"

void kernel_main(void) {
    vga_init();

    vga_print("Hello, kernel world!\n");

    for(size_t i = 0; i < 10; i++) {
        vga_print("i'm so cool i followed an osdev wiki tutorial and maybe it works?\n");
    }

    for(size_t i = 0; i < 10; i++) {
        vga_print("weed\n");
    }

    for(size_t i = 0; i < 10; i++) {
        vga_print("some other thing\n");
    }

    vga_print("weed\n");

    vga_print_color(VGA_COLOR(VGA_COLOR_GREEN, VGA_COLOR_BLACK), "something!\n");
    vga_print_color(VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_GREEN), "something!\n");
    vga_print_color(VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_RED), "something!\n");
}