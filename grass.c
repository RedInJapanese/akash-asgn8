#include "field.h"
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define OPTIONS "aswrvhi:n:S:"

void usage(char *exec) {
  fprintf(
      stderr,
      "SYNOPSIS\n"
      "	Compare different methods of touching grass\n"
      "USAGE\n"
      "	%s [OPTIONS]\n"
      "OPTIONS"
      "	-a		Test all methods.\n"
      "	-s		Test the sequential method.\n"
      "	-w		Test the wide method.\n"
      "	-r		Test the random method.\n"
      "	-v		Show verbose statistics.\n"
      "	-h		Print this help information.\n"
      "	-i iters	Set the number of iterations to run(default: size^2).\n"
      "	-n size		Set the size of the field of grass(1-1024, default: "
      "10).\n"
      "	-S seed		Set the random seed for -r (default: 7566707).\n",
      exec);
}

int main(int argc, char **argv) {
  int opt = 0;
  bool verbose = false;
  bool seq = false;
  bool wide = false;
  bool ran = false;
  uint32_t size = 10;
  uint32_t iters = 100;
  unsigned int seed = 7566707;

  while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
    switch (opt) {
    case 'a':
      seq = true;
      wide = true;
      ran = true;
      break;
    case 's':
      seq = true;
      break;
    case 'w':
      wide = true;
      break;
    case 'r':
      ran = true;
      break;
    case 'v':
      verbose = true;
      break;
    case 'h':
      usage(argv[0]);
      break;
    case 'i':
      iters = (uint32_t)strtoul(optarg, NULL, 10);
      break;
    case 'n':
      size = (uint32_t)strtoul(optarg, NULL, 10);
      break;
    case 'S':
      seed = (unsigned int)strtoul(optarg, NULL, 10);
      break;
    }
  }
  Field *f = field_create(size);
  if (seq) {
    puts("Sequential: ");
    field_touch_sequential(f, iters, seed);
    field_print(f);
    if (verbose) {
      uint32_t eff;
      eff = 100 * (field_count(f) / field_writes(f));
      printf("Touched Blades:		%u\n", field_count(f));
      printf("BitVector writes:	%u\n", field_writes(f));
      printf("Efficiency:		%u percent\n", eff);
    }
  }
  if (wide) {
    puts("Wide: ");
    field_touch_wide(f, iters, seed);
    field_print(f);
    if (verbose) {
      uint32_t eff;
      eff = 100 * (field_count(f) / field_writes(f));
      printf("Touched Blades:		%u\n", field_count(f));
      printf("BitVector writes:	%u\n", field_writes(f));
      printf("Efficiency:		%u percent\n", eff);
    }
  }
  if (ran) {
    puts("Random: ");
    field_touch_random(f, iters, seed);
    field_print(f);
    if (verbose) {
      uint32_t eff;
      eff = 100 * (field_count(f) / field_writes(f));
      printf("Touched Blades:		%u\n", field_count(f));
      printf("BitVector writes:	%u\n", field_writes(f));
      printf("Efficiency:		%u percent\n", eff);
    }
  }
}
