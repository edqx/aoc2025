#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "solution.h"

typedef struct {
  long long start;
  long long end;
} fresh_ingredients;

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

    ingredient_ranges[num_fresh_ingredients++] = range;
  }

process_ingredients:;
  int num_safe_ingredients = 0;

  char expect_newline;
  if (fread(&expect_newline, 1, 1, file) != 1) return AOC_BAD_FORMAT;
  if (expect_newline != '\n') return AOC_BAD_FORMAT;

  while (1) {
    long long ingredient_id;
    switch (fscanf(file, "%lld\n", &ingredient_id)) {
      case EOF:
        printf("num safe ingredients: %d", num_safe_ingredients);
        return AOC_EXIT;
      case 1: break;
      default: return AOC_BAD_FORMAT;
    }

    for (int i = 0; i < num_fresh_ingredients; i++) {
      fresh_ingredients range = ingredient_ranges[i];
      if (ingredient_id < range.start) continue;
      if (ingredient_id > range.end) continue;

      num_safe_ingredients++;
      break;
    }
  }
}

