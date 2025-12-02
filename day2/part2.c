#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "solution.h"

int digits(long long num) {
  return log10(num)+1;
}

char is_repeat(long long full, long long sub) {
  long long fdigits, sdigits, lsplace, msplace, ls, ms, a, comb;
  
  fdigits = digits(full);
  sdigits = digits(sub);
  assert(fdigits % sdigits == 0);

  int parts = fdigits / sdigits;

  comb = -1;
  
  for (int i = 0; i < parts; i++) {
    // basically, the idea here is to isolate the n'th section of the larger number
    // where the size of the section is digits(sub)
    //
    // we do this by taking the least sigificant part (the part below the section)
    // and the most significant part (the part above the section), taking them from
    // eachother to get a number like 000512000 from 512512512, and then dividing to
    // get that as a smaller integer, i.e., 512
    lsplace = pow(10, sdigits * i);
    msplace = pow(10, sdigits * (i + 1));
    
    ls = full / lsplace;
    ms = full / msplace;

    a = ((ls * lsplace) - (ms * msplace)) / lsplace;

    // is this smaller integer equal to every other smaller integer so far?
    if (comb == -1) comb = a;
    if (comb != a) return 0;
  }
  
  return 1;
}

int solution(FILE *file) {
  long long i, dig, part, place, sub;
  
  long long total = 0;
  
  while (1) {
    long long start_id, end_id;

    switch (fscanf(file, "%lld-%lld", &start_id, &end_id)) {
      case 2: break;
      default: return AOC_BAD_FORMAT;
    }

    for (long long i = start_id; i <= end_id; i++) {
      dig = digits(i);
      for (int j = 1; j < dig; j++) {
        // split the larger integer into repeatable sections, i.e., section sizes that divide
        // into digits(i)
        if (dig % j == 0) {
          // take the most significant section as a base to check if it repeats
          part = dig - j;
          place = pow(10, part);

          sub = i / place;

          if (is_repeat(i, sub)) {
            total += i;
            break;
          }
        }
      }
    }

    // quit on EOF or non-comma delimiter, e.g. newline in lf-terminated file
    char delim;
    switch (fscanf(file, "%c", &delim)) {
      case EOF:
        printf("Total: %lld", total);
        return AOC_EXIT;
      case 1: break;
      default: return AOC_BAD_FORMAT;
    }

    if (delim != ',') {
      printf("Total: %lld", total);
      return AOC_EXIT;
    }
  }
}
