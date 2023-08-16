#include "common.h"

size_t strlen(const char* str) {
    size_t len = 0;
    while(str[len]) len++;
    return len;
}

void* memcpy(void* dest, const void* src, size_t n) {
    char* dest_char = (char*)dest;
    const char* src_char = (const char*)src;
    for(size_t i = 0; i < n; i++) {
        dest_char[i] = src_char[i];
    }
    return dest;
}

void* memset(void* dest, int val, size_t n) {
    char* dest_char = (char*)dest;
    for(size_t i = 0; i < n; i++) {
        dest_char[i] = val;
    }
    return dest;
}
