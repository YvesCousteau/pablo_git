#include "header.h"

char* getsecret() {
  char* secret = malloc(7*sizeof(char));
  // Code très secret et obfusqué qui remplit secret
  return secret;
}

void fail() {
  fprintf(stderr, "password not valid\n");
  exit(1);
}

void win() {
  printf("You Win!\n");
}

int main(int argc, char **argv) {
  if (argc != 2) fail();
  if (strcmp(argv[1], getsecret()) != 0) fail();
  win();
}
