#include <stdint.h>

#include "io/vga.h"
#include "std/math.h"
#include "std/vec.h"

// Constants

#define MAX_STEPS 100
#define MAX_DIST  100
#define SURF_DIST .01

// Raymarching functions

float get_dist(v3f p) {
  v3f sphere = { .x = 0, .y = 1, .z = 6 };
  float sphere_r = 1.0;

  float dS = v3f_mag(v3f_subvv(p, sphere)) - sphere_r;
  float dP = p.y;

  float d = fmin(dS, dP);
  return d;
}

float raymarch(v3f ro, v3f rd) {
  float dO = 0;

  for (int i = 0; i < MAX_STEPS; ++i) {
    v3f p = v3f_addvv(ro, v3f_mulvf(rd, dO));
    float dS = get_dist(p);
    dO += dS;
    if (dO > MAX_DIST || dS < SURF_DIST) break;
  }

  return dO;
}


// Misc functions

float map(float x, float imin, float imax, float omin, float omax) {
  return (x - imin) * (omax - omin) / (imax - imin) + omin;
}

// Screen functions

void draw() {
  for (int y = 0; y < RES_Y; ++y) {
    for (int x = 0; x < RES_X; ++x) {
      float u = (((float)x) - 0.5 * RES_X) / RES_Y;
      float v = (((float)y) - 0.5 * RES_Y) / RES_Y;

      v3f ro = { .x = 0, .y = 1, .z = 0 };
      v3f rd = { .x = u, .y = v, .z = 1 };
      rd = v3f_norm(rd);

      float d = raymarch(ro, rd);
      d /= 6.0;

      if (d > 1.0) d = 1.0;
      int col = (int)map(d, 0, 1, 0, 255);

      putpixel(x, y, col);
    }
  }
}

// Entrypoint

void _start() {
  // Set color palette to grayscale
  // Channels are 6-bit!
  for (int i = 1; i < 256; ++i) {
    uint8_t r = (int)map(i, 0, 255, 0, 63);
    uint8_t b = (int)map(i, 0, 255, 0, 63);
    uint8_t g = (int)map(i, 0, 255, 0, 63);
    set_palette(i, r, g, b);
  }

  draw();
}
