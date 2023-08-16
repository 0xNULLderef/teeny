#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

size_t strlen(const char* str);
void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* dest, int val, size_t n);

#endif
