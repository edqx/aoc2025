#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: ./part1 <input file name>\n");
    exit(1);
  }
  
  char* file_name = argv[1];

  FILE* file = fopen(file_name, "r");

  if (file == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(1);
  }

  int dial = 50;
  int times_we_hit_0 = 0;

  while (1) {
    char dir;
    int num;

    switch (fscanf(file, "%1c%3d\n", &dir, &num)) {
      case EOF: goto leave;
      case 2: break;
      default:
        fprintf(stderr, "Improperly formatted file\n");
        fclose(file);
        exit(1);
        break;
    }

    num = num % 100;
    if (dir == 'L') num = -num;

    dial += num;

    if (dial > 99) dial -= 100;
    if (dial < 0) dial += 100;

    if (dial == 0) times_we_hit_0 ++;
  }

leave:
  printf("Password: %d", times_we_hit_0);

  fclose(file);
}
