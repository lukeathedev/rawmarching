#include <stdint.h>

#include "vga.h"
#include "io.h"

// idx starts at 1
void set_palette(uint8_t idx, uint8_t r, uint8_t g, uint8_t b) {
  outb(VGA_SET_PALETTE, idx);
  outb(VGA_SET_COLOR, r);
  outb(VGA_SET_COLOR, g);
  outb(VGA_SET_COLOR, b);
}

void putpixel(uint16_t x, uint16_t y, uint8_t color) {
  volatile char* video_mem = (volatile char* ) VGA_VIDEO_MEM;
  video_mem += x + y * RES_X;

  *video_mem = color;
}
