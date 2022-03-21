#include "field.h"
#include <stdio.h>
#include <stdlib.h>

struct Field {
  uint32_t size;
  BitVector *matrix;
};

Field *field_create(uint32_t size) {
  Field *f = (Field *)malloc(sizeof(Field));
  f->size = size;
  f->matrix = bv_create(size * size);
  return f;
}

void field_delete(Field **f) {
  bv_delete(&(*f)->matrix);
  free(*f);
  *f = NULL;
}

uint32_t field_size(Field *f) { return f->size; }

uint32_t field_area(Field *f) { return (f->size) * (f->size); }

uint32_t field_count(Field *f) {
  bool bit = false;
  uint32_t count = 0;
  for (uint32_t i = 0; i < (field_size(f) * field_size(f)); i++) {
    if (bv_get_bit(f->matrix, i, &bit)) {
      count++;
    }
  }
  return count;
}

uint32_t field_writes(Field *f) { return bv_writes(f->matrix); }

void field_touch_sequential(Field *f, uint32_t max_iters, unsigned int seed) {
  seed = 0;
  if (max_iters > field_size(f)) {
    return;
  }
  for (uint32_t i = 0; i < max_iters; i++) {
    bv_set_bit(f->matrix, i);
  }
}

void field_touch_wide(Field *f, uint32_t max_iters, unsigned int seed) {
  seed = 0;
  if (max_iters > field_size(f)) {
    return;
  }
  for (uint32_t i = 0; i < max_iters; i++) {
    bv_set_64(f->matrix, i);
  }
}

void field_touch_random(Field *f, uint32_t max_iters, unsigned int seed) {
  if (max_iters > field_size(f)) {
    return;
  }
  for (uint32_t i = 0; i < max_iters; i++) {
    srandom(seed);
    bv_set_bit(f->matrix, random() % field_size(f));
  }
}

void field_print(Field *f) { bv_print(f->matrix); }
