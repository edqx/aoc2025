#include <stdlib.h>
#include <stdio.h>

#include "solution.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: ./solution <input file name>\n");
    exit(1);
  }
  
  char* file_name = argv[1];

  FILE *file = fopen(file_name, "r");

  if (file == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(1);
  }

  switch (solution(file)) {
    case AOC_EXIT: break;
    case AOC_BAD_FORMAT:
      fprintf(stderr, "Improperly formatted file\n");
      fclose(file);
      exit(1);
      break;
  }

  fclose(file);
  exit(0);
}
