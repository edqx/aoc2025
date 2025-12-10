#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "solution.h"

#define MAX_LINE 512

#define BEAM '|'
#define SPACE '.'
#define SPLIT '^'
#define START 'S'

void split_beam(int len, int *beams, int i) {
  if (i > 0) {
    beams[i - 1] += beams[i];
  }

  if (i < len - 1) {
    beams[i + 1] += beams[i];
  }

  beams[i] = 0;
}

void transform_line(int *beams, int len, char* line, int *num_splits) {
  for (int i = 0; i < len; i++) {
    char op = line[i];

    switch (op) {
    case BEAM: break;
    case SPACE: break;
    case SPLIT:
      if (beams[i] > 0) {
        split_beam(len, line, i);
      }
      break;
    case START:
      beams[i]++;
      break;
    }
  }
}

int solution(FILE *file) {
  int beams[MAX_LINE];
  memset(beams, 0, sizeof(int) * MAX_LINE);

  char current_line[MAX_LINE];
  memset(current_line, SPACE, MAX_LINE);

  int num_splits = 0;

  while (1) {
    switch (fscanf(file, "%s", current_line)) {
    case 1: break;
    default: goto leave;
    }

    int len = strlen(current_line);
    transform_line(beams, len, current_line, &num_splits);
    for (int i = 0; i < len; i++) {
      printf("%d ", beams[i]);
    }
    printf("\n");
  }

leave:
  printf("Number of splits: %d\n", num_splits);
  return AOC_EXIT;
}