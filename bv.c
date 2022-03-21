#include "bv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BitVector {
  uint32_t length;
  uint64_t *vector;
  uint32_t writes;
};

BitVector *bv_create(uint32_t size) {
  BitVector *bv = (BitVector *)malloc(sizeof(BitVector));
  bv->length = size;
  bv->writes = 0;
  uint64_t bytes = size / 64 + (size % 64 ? 1 : 0);
  bv->vector = (uint64_t *)calloc(bytes, sizeof(uint64_t));
  return bv;
}

void bv_delete(BitVector **bv) {
  /*for(uint64_t i = 0; i<(*bv)->length; i++) {
          free((*bv)->vector[i]);
          (*bv)->vector[i] = NULL;
  }*/
  free((*bv)->vector);
  (*bv)->vector = NULL;
  free((*bv));
  (*bv) = NULL;
}

uint32_t bv_length(BitVector *bv) { return bv->length; }

bool bv_set_bit(BitVector *bv, uint32_t i) {
  if (i < bv->length && i >= 0) {
    bv->vector[i / 64] |= (0x1 << i % 64);
    bv->writes += 1;
    return true;
  }
  return false;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
  if (i < bv->length && i >= 0) {
    bv->vector[i / 64] &= ~(0x1 << i % 64);
    bv->writes += 1;
    return true;
  }
  return false;
}

bool bv_get_bit(BitVector *bv, uint32_t i, bool *bit) {
  if (i < bv->length && i >= 0) {
    if ((bv->vector[i / 64] >> i % 64) & 0x1) {
      *bit = true;
      return *bit;
    }
    *bit = false;
    return *bit;
  }
  return false;
}

bool bv_set_64(BitVector *bv, uint32_t i) {
  if (i < bv->length && i >= 0) {
    memset(&bv->vector[i / 64], 255, 8);
    bv->writes += 1;
    return true;
  }
  return false;
}

bool bv_clr_64(BitVector *bv, uint32_t i) {
  if (i < bv->length && i >= 0) {
    bv->vector[i / 64] = 0;
    bv->writes += 1;
    return true;
  }
  return false;
}

uint32_t bv_writes(BitVector *bv) { return bv->writes; }

void bv_print(BitVector *bv) {
  bool bit = false;
  // puts("test1");
  for (uint64_t i = 0; i < bv_length(bv); i++) {
    // puts("test2");
    if (bv_get_bit(bv, i, &bit)) {
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");
}
