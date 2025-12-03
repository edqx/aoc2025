#include <stdio.h>
#include <stdlib.h>

#include "solution.h"

int solution(FILE *file) {
  int dial = 50;
  int times_we_hit_0 = 0;

  while (1) {
    char dir;
    int num;

    switch (fscanf(file, "%1c%3d\n", &dir, &num)) {
      case EOF:
        printf("Password: %d\n", times_we_hit_0);
        return AOC_EXIT;
      case 2: break;
      default: return AOC_BAD_FORMAT;
    }

    num = num % 100;
    if (dir == 'L') num = -num;

    dial += num;

    if (dial > 99) dial -= 100;
    if (dial < 0) dial += 100;

    if (dial == 0) times_we_hit_0 ++;
  }
}
