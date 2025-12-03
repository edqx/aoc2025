#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "solution.h"

int solution(FILE *file) {
  long long total = 0;
  
  while (1) {

    char buf[512];
    if (fgets(buf, 512, file) == NULL) {
      printf("Total: %lld\n", total);
      return AOC_EXIT;
    }

    int len = strlen(buf);

    if (buf[len - 1] == '\n') {
      buf[len - 1] = '\0';
      len -= 1;
    }

    // we actually store the indexes of the max joltages, because we can use those indices to carry on
    // for the next digit
    char joltages_i[12];
    long long joltage = 0;

    // basically just find each biggest integer one after another. e.g. find a '9' that comes first, then an '8' after that,
    // then a '6' after that.
    for (int i = 0; i < 12; i++) {
      int last_i = i == 0 ? 0 : joltages_i[i - 1] + 1;
      int digits_left = 12 - i - 1;

      int max_joltage_i = last_i;
      for (int j = last_i + 1; j < len - digits_left; j++) {
        char digit = buf[j];
        if (digit < '0' || digit > '9') return AOC_BAD_FORMAT;

        char joltage = digit;
        if (joltage > buf[max_joltage_i]) {
          max_joltage_i = j;
        }
      }
      joltages_i[i] = max_joltage_i;
      joltage += (buf[max_joltage_i] - '0') * pow(10, digits_left);
    }

    total += joltage;
  }
}
