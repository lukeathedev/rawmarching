#include <stdint.h>

#include "vga.h"

// TODO: implement sleep function for fixed framerate

double pow(double x, int b) {
  double res = x;
  for (int i = 1; i < b; ++i) {
    res *= x;
  }

  return res;
}

void draw(int xoff) {
  int r = 40;

  for (int y = 0; y < 200; ++y) {
    for (int x = 0; x < 320; ++x) {
      if (pow((double)x-(xoff), 2)+pow((double)y-r, 2) < pow(r, 2)) {
        putpixel(x, y, (x-xoff)*(x-xoff)%0b1111);
      }
      else {
        putpixel(x, y, 0);
      }
    }
  }
}

void _start(){
  // int x = 0;
  // int y = 6;

  // print(0b00101111, "[INFO]  Kernel called at 0x10000", &x, &y);
  // y++;
  // print(0b00000111, "[INFO]  Switching to VGA 640x480 16-color", &x, &y);

  double xoff = 0;
  int dir = 1;

  for (;;) {
    xoff+=0.025 * dir;
    if (xoff > 360) dir *= -1;
    if (xoff < -40) dir *= -1;
    draw(xoff);
  }
}
