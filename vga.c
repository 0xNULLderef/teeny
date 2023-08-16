#include "vga.h"

#include <stddef.h>
#include "common.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
//#define VGA_BUFFER_BASE 0xB8000
#define VGA_BUFFER_BASE 0xC03FF000

#define VGA_COLOR_DEFAULT VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_BLACK)

struct VGA_CHAR {
    char character;
    uint8_t color;
};

struct VGA {
    size_t row;
    size_t column;
    struct VGA_CHAR* buffer;
};

static struct VGA vga;

void vga_init(void) {
    vga.row = 0;
    vga.column = 0;
    vga.buffer = (struct VGA_CHAR*)VGA_BUFFER_BASE;
    memset(vga.buffer, 0, VGA_WIDTH * VGA_HEIGHT * sizeof(struct VGA_CHAR));
}

void vga_advance_line(void) {
    if(vga.column < VGA_HEIGHT - 1) {
        vga.column++;
    } else {
        // uhhhhhh-
        memcpy(vga.buffer, &vga.buffer[VGA_WIDTH], VGA_WIDTH * (VGA_HEIGHT - 1) * sizeof(struct VGA_CHAR));
        memset(&vga.buffer[VGA_WIDTH * (VGA_HEIGHT - 1)], 0, VGA_WIDTH * sizeof(struct VGA_CHAR));
    }
}

void vga_advance_char(void) {
    if(++vga.row == VGA_WIDTH) {
        vga.row = 0;
        vga_advance_line();
    }
}

void vga_put_vga_char(struct VGA_CHAR vga_char) {
    switch(vga_char.character) {
        case '\r':
            vga.row = 0;
            break;
        case '\n':
            vga.row = 0;
            vga_advance_line();
            break;
        default:
            vga.buffer[vga.column * VGA_WIDTH + vga.row] = vga_char;
            vga_advance_char();
            break;
    }
}

void vga_print_color(uint8_t color, const char* str) {
    struct VGA_CHAR vga_char;
    vga_char.color = color;
    for(size_t i = 0; i < strlen(str); i++) {
        vga_char.character = str[i];
        vga_put_vga_char(vga_char);
    }
}

void vga_print(const char* str) {
    vga_print_color(VGA_COLOR_DEFAULT, str);
}
