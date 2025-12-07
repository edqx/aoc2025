#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solution.h"

#define MAX_NUMBERS 4096
#define MAX_DIGITS 5

int solution_impl(char *buf, int file_size, long long *result) {
  char *line;
  char *newl = buf;

  (*result) = 0;

  long long numbers[MAX_NUMBERS];
  memset(numbers, 0, sizeof(long long) * MAX_NUMBERS);

  int digit = 0;
  while ((line = strtok_r(newl, "\n", &newl))) {
    if (line[0] == '+' || line[0] == '*') {
      char last_op = line[0];
      long long subtotal = 0;
      for (char *p = line; *p != '\0'; p++) {
        char d = *p;
        int col = p - line;
        if (d != ' ') {
          (*result) += subtotal;
          subtotal = 0;
          last_op = d;
        }

        if (numbers[col] == 0) continue;

        if (last_op == '+') {
          subtotal += numbers[col];
        } else if (last_op == '*') {
          if (subtotal == 0) subtotal = 1;
          subtotal *= numbers[col];
        } else return AOC_BAD_FORMAT;
      }

      (*result) += subtotal;
      break;
    }
    
    // Use -1 to remove the null byte at the end
    for (char *p = line + strlen(line) - 1; p >= line; p--) {
      char d = *p;
      int col = p - line;
      if (d == ' ') continue;
      if (d < '0' && d > '9') return AOC_BAD_FORMAT;
      
      numbers[col] *= 10;
      numbers[col] += d - '0';
    }
    digit++;
  }
  return AOC_EXIT;
}

int solution(FILE *file) {
 // windows translates \r\n to \n so it seems impossible to get the file size properly with one or two calls
  fseek(file, 0, SEEK_END);
  int file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  char *buf = calloc(file_size, 1);
  fread(buf, 1, file_size, file);
  
  long long result;
  int code = solution_impl(buf, file_size, &result);
  free(buf);
  if (code == AOC_EXIT) {
    printf("Total: %lld\n", result);
  }
  return code;
}
