#include <stdint.h>

#include "io/vga.h"
#include "std/math.h"
#include "std/vec.h"

// Constants

#define MAX_STEPS 100
#define MAX_DIST  100
#define SURF_DIST .01

int FRAME;

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

// Quite ugly code
v3f get_normal(v3f p) {
  float d = get_dist(p);
  float epsilon = 0.25;

  v3f xc = {
    .x = p.x - epsilon,
    .y = p.y,
    .z = p.z
  };

  v3f yc = {
    .x = p.x,
    .y = p.y - epsilon,
    .z = p.z
  };

  v3f zc = {
    .x = p.x,
    .y = p.y,
    .z = p.z - epsilon
  };

  v3f test = {
    .x = get_dist(xc),
    .y = get_dist(yc),
    .z = get_dist(zc)
  };

  v3f n = v3f_subfv(d, test);

  return v3f_norm(n);
}

float get_light(v3f p) {
  v3f light_pos = { .x = 20, .y = 8, .z = 26 };
  v3f l = v3f_mulvf(v3f_norm(v3f_subvv(light_pos, p)), 0.5);
  v3f n = get_normal(p);

  float dif = clamp(v3f_dot(n, l), 0, 1);
  float d = raymarch(v3f_addvv(p, v3f_mulvf(n, SURF_DIST * 2)), l);
  if (d < v3f_mag(v3f_subvv(light_pos, p))) dif *= 0.1;

  return dif;
}

// Misc functions

float map(float x, float imin, float imax, float omin, float omax) {
  float ret = (x - imin) * (omax - omin) / (imax - imin) + omin;
  // if (ret > omax) return omax;
  // if (ret < omin) return omin;
  return ret;
}

// Screen functions

void draw() {
  for (int y = 0; y < RES_Y; ++y) {
    for (int x = 0; x < RES_X; ++x) {
      float u = (((float)x) - 0.5 * RES_X) / RES_Y;
      // y coord is reversed
      float v = (((float)RES_Y-y) - 0.5 * RES_Y) / RES_Y;

      v3f ro = { .x = -1+(float)FRAME/10, .y = 1, .z = 2 };
      v3f rd = { .x = u, .y = v, .z = 1 };
      rd = v3f_norm(rd);

      float d = raymarch(ro, rd);

      v3f p = v3f_addvv(ro, v3f_mulvf(rd, d));

      float dif = get_light(p);
      // float dif = get_normal(p).y;
      int col = (int)map(dif, 0, 1, 0, 255);

      putpixel(x, y, col);
    }
  }
}

// Entrypoint

void _start() {
  FRAME = 0;

  // Set color palette to grayscale
  // Channels are 6-bit!
  for (int i = 1; i < 256; ++i) {
    uint8_t r = (int)map(i, 0, 255, 0, 63);
    uint8_t b = (int)map(i, 0, 255, 0, 63);
    uint8_t g = (int)map(i, 0, 255, 0, 63);
    set_palette(i, r, g, b);
  }

  int i = 0;

  for (;;) {
    draw();
    FRAME++;
  }
}
