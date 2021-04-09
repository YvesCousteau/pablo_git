#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0
#define SIZE 10000

int main(void)
{
  srand( time( NULL ) );

  int tab[SIZE];


  pid_t pid = fork();

  if (pid == -1) {
    perror("fork failed");
  }
  else if (pid == 0) {
    for (int i = SIZE/2; i < SIZE; i++) {
      tab[i]=rand() % 10001;
      if (tab[i]==42) {
        printf("indice %d = 42\n",i );
      }
    }
  }
  else {
    for (int i = 0; i < SIZE/2; i++) {
      tab[i]=rand() % 10001;
      if (tab[i]==42) {
        printf("indice %d = 42\n",i );
      }
    }
    waitpid(pid,NULL,0);
  }
  return EXIT_SUCCESS;
}
