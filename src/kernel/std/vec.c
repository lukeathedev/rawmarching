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

v3f v3f_subfv(float a, v3f b) {
  v3f c = {
    .x = a - b.x,
    .y = a - b.y,
    .z = a - b.z
  };
  return c;
}

v3f v3f_subvf(v3f a, float b) {
  v3f c = {
    .x = a.x - b,
    .y = a.y - b,
    .z = a.z - b
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
  return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

v3f v3f_norm(v3f a) {
  float mag = v3f_mag(a);
  return v3f_divvf(a, mag);
}

float v3f_dot(v3f a, v3f b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
