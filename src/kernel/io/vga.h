#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VGA_GET_PALETTE 0x03C7
#define VGA_SET_PALETTE 0x03C8
#define VGA_SET_COLOR   0x03C9

#define VGA_VIDEO_MEM   0xA0000
#define RES_X           320
#define RES_Y           200

// https://www.cprogramming.com/tutorial/tut2.html
void set_palette(uint8_t idx, uint8_t r, uint8_t g, uint8_t b);

void putpixel(uint16_t x, uint16_t y, uint8_t color);

#endif
