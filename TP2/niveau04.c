#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void win() {
  printf("Win !\n");
}

void check_credentials() {
  char buffer[64];
  gets(buffer);
}

int main(int argc, char **argv) {
  check_credentials();
}
