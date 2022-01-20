#include "vec.h"
#include "math.h"

v3f v3f_addvv(v3f a, v3f b) {
  v3f c = {
    .x = a.x + b.x,
    .y = a.y + b.y,
    .z = a.z + b.z
  };
  return c;
}

v3f v3f_subvv(v3f a, v3f b) {
  v3f c = {
    .x = a.x - b.x,
    .y = a.y - b.y,
    .z = a.z - b.z
  };
  return c;
}

v3f v3f_mulvf(v3f a, float b) {
  v3f c = {
    .x = a.x * b,
    .y = a.y * b,
    .z = a.z * b
  };
  return c;
}

v3f v3f_divvf(v3f a, float b) {
  v3f c = {
    .x = a.x / b,
    .y = a.y / b,
    .z = a.z / b
  };
  return c;
}

// https://www.khanacademy.org/computing/computer-programming/programming-natural-simulations/programming-vectors/a/vector-magnitude-normalization
float v3f_mag(v3f a) {
  float c = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
  return c;
}

v3f v3f_norm(v3f a) {
  float mag = v3f_mag(a);
  return v3f_divvf(a, mag);
}
