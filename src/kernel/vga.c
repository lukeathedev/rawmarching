#include <stdint.h>

#include "vga.h"

void putpixel(uint16_t x, uint16_t y, uint16_t color) {
  volatile char* video = (volatile char* ) 0xA0000;
  video += x + y * 320;

  *video = color;
}

void print(int colour, const char *string, int* x, int* y)
{
    volatile char* video = (volatile char* ) 0xB8000;
    video +=  ((*y) * 160) + (*x);

    while (*string != 0)
    {
        *video++ = *string++;
        *video++ = colour;
    }
}
