#ifndef VGA_H
#define VGA_H

#include <stdint.h>

void putpixel(uint16_t x, uint16_t y, uint16_t color);
void print(int colour, const char *string, int* x, int* y);

#endif
