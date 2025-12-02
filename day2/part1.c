#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "solution.h"

int solution(FILE *file) {
  long long i, digits, half, place, a, b;
  
  long long total = 0;
  
  while (1) {
    long long start_id, end_id;

    switch (fscanf(file, "%lld-%lld", &start_id, &end_id)) {
      case 2: break;
      default: return AOC_BAD_FORMAT;
    }

    i = start_id;
    while (i <= end_id) {
      // add '1' because we are working with integer logarithms
      digits = log10(i)+1;
      // odd-length numbers cant have repeats
      if (digits % 2 == 0) {
        // this gives us the base place of what would be
        // half of an id, e.g. for 885300, this would give us 100.
        half = digits / 2;
        place = pow(10, half);

        // for 885300, this gives us the 885 part
        b = i / place;
        // using b, we can then remove the first part from the id.
        // we're abusing integer division/multiplication here but
        // that's ok
        a = i - (b * place);

        if (a == b) {
          total += i;
        }
      }
      i += 1;
    }

    char delim;
    switch (fscanf(file, "%c", &delim)) {
      case EOF: goto total;
      case 1: break;
      default: return AOC_BAD_FORMAT;
    }

    if (delim != ',') goto total;
  }

total:
  printf("Total: %lld", total);
  return AOC_EXIT;
}
