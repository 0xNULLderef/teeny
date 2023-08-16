#include <stddef.h>
#include <stdint.h>

#include "vga.h"

void kernel_main(void) {
    vga_init();

    vga_print("Hello, kernel world!\n");
}
