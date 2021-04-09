#include "header.h"

extern char secret[];

void fail() {
  fprintf(stderr, "password not valid\n");
  exit(1);
}

void win() {
  printf("You Win!\n");
}

int main(int argc, char **argv) {
  if (argc != 2) fail();
  if (strcmp(argv[1], secret) != 0) fail();
  win();
}
