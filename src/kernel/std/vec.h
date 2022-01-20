#ifndef STD_VEC_H
#define STD_VEC_H

typedef struct {
  float x, y, z;
} v3f;

v3f v3f_addvv(v3f a, v3f b);
v3f v3f_subvv(v3f a, v3f b);
v3f v3f_mulvf(v3f a, float b);
v3f v3f_divvf(v3f a, float b);
float v3f_mag(v3f a);
v3f v3f_norm(v3f a);

#endif
