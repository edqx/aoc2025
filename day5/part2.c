#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "solution.h"

typedef struct {
  long long start;
  long long end;
} fresh_ingredients;

long long count_range(fresh_ingredients a) {
  return a.end - a.start;
}

void clear(fresh_ingredients *a) {
  (*a) = (fresh_ingredients){ .start = 0, .end = 0 };
}

int solution(FILE *file) {
  // let's set this to 0 so we have sentinels for free
  fresh_ingredients *ingredient_ranges = calloc(512, sizeof(fresh_ingredients));
  int num_fresh_ingredients = 0;
  
  while (1) {
    fresh_ingredients range;
    switch (fscanf(file, "%lld-%lld\n", &range.start, &range.end)) {
      case EOF: return AOC_BAD_FORMAT;
      case 2: break;
      default: goto process_ingredients;
    }

    range.end++;

    ingredient_ranges[num_fresh_ingredients++] = range;
  }

process_ingredients:;
  char expect_newline;
  if (fread(&expect_newline, 1, 1, file) != 1) return AOC_BAD_FORMAT;
  if (expect_newline != '\n') return AOC_BAD_FORMAT;

  fresh_ingredients *new_ranges = calloc(512, sizeof(fresh_ingredients));
  int num_new_ranges = 0;

  // de-dupe range list algorithm, really bad but whatevs dude!
  while (1) {
    char flag2 = 0;

    for (int i = 0; i < num_fresh_ingredients; i++) {
      fresh_ingredients *range = &ingredient_ranges[i];

      if (range->start == 0 && range->end == 0) continue;

      for (int j = 0; j < num_fresh_ingredients; j++) {
        if (i == j) continue;
        fresh_ingredients *range2 = &ingredient_ranges[j];

        char flag = 0;

        // lies within
        if (range2->start >= range->start && range2->end <= range->end) {
          flag = 1;
        }

        // range2 goes beyond range1
        if (range2->start >= range->start && range2->start <= range->end && range2->end > range->end) {
          range->end = range2->end;
          flag = 1;
        }

        // range2 goes before range1
        if (range2->end <= range->end && range2->end >= range->start && range2->start < range->start) {
          range->start = range2->start;
          flag = 1;
        }

        if (flag) {
          // let's keep going
          flag2 = 1;
          clear(range2);
        }
      }
    }

    if (!flag2) break;
  }

  long long total = 0;

  for (int i = 0; i < num_fresh_ingredients; i++) {
    total += count_range(ingredient_ranges[i]);
  }

  printf("num fresh ingredients: %lld\n", total);

  return AOC_EXIT;
}

