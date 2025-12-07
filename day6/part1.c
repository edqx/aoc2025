#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solution.h"

#define MAX_TOTALS 2048

int solution_impl(char *buf, int file_size, long long *result) {
  char *line;
  char *newl = buf;

  (*result) = 0;

  // store both the * total and the + total, since we don't know the operation until the end
  long long subtotals[MAX_TOTALS][2];
  for (int i = 0; i < MAX_TOTALS; i++) {
    subtotals[i][0] = 1; // mult. identity
    subtotals[i][1] = 0; // add. identity
  }

  while ((line = strtok_r(newl, "\n", &newl))) {
    char *token;
    char *sp = line;
    int num = 0;
    while ((token = strtok_r(sp, " ", &sp))) {
      switch (token[0]) {
      case '*':
        (*result) += subtotals[num][0];
        break;
      case '+':
        (*result) += subtotals[num][1];
        break;
      default:;
        long long op = strtoll(token, 0, 0);
        subtotals[num][0] *= op;
        subtotals[num][1] += op;
        break;
      }
      num++;
    }
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
