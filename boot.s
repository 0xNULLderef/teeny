extern _kernel_start
extern _kernel_end
extern kernel_main

section .multiboot.data align=4
dd 0x1BADB002 ; magic
dd 3 ; flags MEMINFO | ALIGN
dd 0xE4524FFB ; checksum, sums to 0

section .bootstrap_stack align=4 nobits
stack_bottom:
resb 16384
stack_top:

section .bss align=4096 nobits
boot_page_directory:
resb 4096
boot_page_table1:
resb 4096

section .multiboot.text align=16
global _start
default rel
_start:
    mov edi, boot_page_table1 - 0xC0000000
    mov esi, 0
    mov ecx, 0x3FF

.1:
    cmp esi, _kernel_start
    jl .2
    cmp esi, _kernel_end - 0xC0000000
    jge .3

    mov edx, esi
    or edx, 3
    mov [edi], edx

.2:
    add esi, 0x1000
    add edi, 4
    loop .1

.3:
    ; map vga @ C03FF000
    mov dword [boot_page_table1 - 0xC0000000 + 0x3FF * 4], 0x000B8000 | 3

    ; map boot_page_table @ 0 & C0000000
    mov dword [boot_page_directory - 0xC0000000], boot_page_table1 - 0xC0000000 + 3
    mov dword [boot_page_directory - 0xC0000000 + 0x300 * 4], boot_page_table1 - 0xC0000000 + 3

    mov ecx, boot_page_directory - 0xC0000000
    mov cr3, ecx

    mov ecx, cr0
    or ecx, 1 << 31 | 1 << 16
    mov cr0, ecx

    lea ecx, [.4]
    jmp ecx

section .text

.4:
    mov dword [boot_page_directory + 0], 0

    mov ecx, cr3
    mov cr3, ecx

    mov esp, stack_top

    call kernel_main

    cli
.5:
    hlt
    jmp .5
