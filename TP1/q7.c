#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0
#define LOOP 10000

int main(void)
{
  pid_t pid = fork();

  if (pid == -1) {
    perror("fork failed");
  }
  else if (pid == 0) {
    for (size_t i = 0; i < LOOP; i++) {
      printf("b");
    }

  }
  else {
    for (size_t i = 0; i < LOOP; i++) {
      printf("a");
    }
    waitpid(pid,NULL,0);
  }
  return EXIT_SUCCESS;
}

// alternative between a and b
