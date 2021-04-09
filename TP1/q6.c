#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

int main(void)
{
  pid_t pid = fork();

  if (pid == -1) {
      perror("fork failed");
  }
  else if (pid == 0) {
      printf("Je suis le fils\n");

  }
  else {
      printf("Je suis le père\n");
      waitpid(pid,NULL,0);
  }
  return EXIT_SUCCESS;
  }
// father first and son second
