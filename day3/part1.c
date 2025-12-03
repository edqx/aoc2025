#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "solution.h"

int solution(FILE *file) {
  int total = 0;
  
  while (1) {

    char buf[512];
    if (fgets(buf, 512, file) == NULL) {
      printf("Total: %d\n", total);
      return AOC_EXIT;
    }

    int len = strlen(buf);

    if (buf[len - 1] == '\n') {
      buf[len - 1] = '\0';
      len -= 1;
    }
    
    // find the first digit. the first highest will also always be
    // the start of the highest 2 digit number in general
    int max_joltage_i = -1;
    for (int i = 0; i < len - 1; i++) {
      char digit = buf[i];
      if (digit < '0' || digit > '9') return AOC_BAD_FORMAT;

      char joltage = digit;
      if (max_joltage_i == -1 || joltage > buf[max_joltage_i]) {
        max_joltage_i = i;
      }
    }

    // find the second digit, also the highest
    int max_joltage_j = -1;    
    for (int j = max_joltage_i + 1; j < len; j++) {
      char digit = buf[j];
      if (digit < '0' || digit > '9') return AOC_BAD_FORMAT;

      char joltage = digit;
      if (max_joltage_j == -1 || joltage > buf[max_joltage_j]) {
        max_joltage_j = j;
      }
    }

    char j1 = buf[max_joltage_i] - '0';
    char j2 = buf[max_joltage_j] - '0';

    total += (j1 * 10) + j2;
  }
}
