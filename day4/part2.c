#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "solution.h"

char exists(char *buf, int size, int col, int row, int line_length) {
  if (col < 0) return 0;
  if (col >= line_length) return 0;
  if (row < 0) return 0;
  int offset = col + (row * line_length);
  if (offset >= size) return 0;

  return buf[offset] == '@' || buf[offset] == '#';
}

int count_adjacent(char *buf, int size, int offset, int line_length) {
  int col = offset % line_length;
  int row = floor(offset / line_length);

  int result = 0;

  // line above
  if (exists(buf, size, col - 1, row - 1, line_length)) result += 1;
  if (exists(buf, size, col,     row - 1, line_length)) result += 1;
  if (exists(buf, size, col + 1, row - 1, line_length)) result += 1;

  // same line
  if (exists(buf, size, col - 1, row,     line_length)) result += 1;
  if (exists(buf, size, col + 1, row,     line_length)) result += 1;

  // line below
  if (exists(buf, size, col - 1, row + 1, line_length)) result += 1;
  if (exists(buf, size, col,     row + 1, line_length)) result += 1;
  if (exists(buf, size, col + 1, row + 1, line_length)) result += 1;

  return result;
}

int solution_impl(char *buf, int size, int *result) {
  int line_length = 0;
  for (; line_length < size && buf[line_length] != '\n'; line_length++);

  line_length++; // include the final '\n' on each line
  
  *result = 0;

  while (1) {
    int num = 0;
    
    for (int i = 0; i < size; i++) {
      if (buf[i] == '@') {
        int adjacent = count_adjacent(buf, size, i, line_length);
        if (adjacent < 4) {
          buf[i] = '#';
          num++;
        }
      } else if (buf[i] == '.' || buf[i] == '\n') {
      
      } else if (buf[i] == '\0') {
        break;
      } else return AOC_BAD_FORMAT;
    }

    for (int i = 0; i < size; i++) {
      if (buf[i] == '#') buf[i] = '.';
    }

    if (num == 0) break;

    (*result) += num;
  }

  return AOC_EXIT;
}

int solution(FILE *file) {
 // windows translates \r\n to \n so it seems impossible to get the file size properly with one or two calls
  fseek(file, 0, SEEK_END);
  int file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  char *buf = malloc(file_size);
  fread(buf, 1, file_size, file);
  
  int result;
  int code = solution_impl(buf, file_size, &result);
  free(buf);
  if (code == AOC_EXIT) {
    printf("Papers: %d\n", result);
  }
  return code;
}
