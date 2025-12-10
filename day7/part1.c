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

void split_beam(int len, char* line, int i) {
  if (i > 0 && line[i - 1] == SPACE) {
    line[i - 1] = BEAM;
  }

  if (i < len - 1 && line[i + 1] == SPACE) {
    line[i + 1] = BEAM;
  }
}

void transform_line(char* above_line, char* line, int *num_splits) {
  assert(strlen(above_line) == strlen(line));

  int len = strlen(line);
  for (int i = 0; i < len; i++) {
    char above_op = above_line[i];
    char op = line[i];

    switch (op) {
    case BEAM: break;
    case SPACE:
      if (above_op == BEAM) line[i] = BEAM;
      break;
    case SPLIT:
      if (above_op == BEAM) {
        split_beam(len, line, i);
        (*num_splits) += 1;
      }
      break;
    case START:
      line[i] = BEAM;
    }
  }
}

int solution(FILE *file) {
  char last_line[MAX_LINE];
  memset(last_line, SPACE, MAX_LINE);

  char current_line[MAX_LINE];
  memset(current_line, SPACE, MAX_LINE);

  int num_splits = 0;

  while (1) {
    switch (fscanf(file, "%s", current_line)) {
    case 1: break;
    default: goto leave;
    }

    int len = strlen(current_line);
    last_line[len] = '\0';

    transform_line(last_line, current_line, &num_splits);

    strcpy(last_line, current_line);
    // printf("%s\n", current_line);
  }

leave:
  printf("Number of splits: %d\n", num_splits);
  return AOC_EXIT;
}