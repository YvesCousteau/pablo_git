#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0
#define SIZE 10000


int main(int argc,char const *argv[]) {
  srand( time( NULL ) );
  int size = strlen(argv[1]);
  char* word = argv[1];
  int check;
  int temp = 0;
  int pui=1;
  for (int i = size; i > 0; i--) {
    check = (word[i-1] - '0');
    if ((check >= 0) || (check <= 9)) {
      temp = temp + check*(pui);
      pui = pui * 10;
    }
  }
  int tab[SIZE];

  pid_t pid[temp];

  for ( i = 0; i < temp; i++) {
    pid[i] = fork();
    if (pid[i] == -1) {
      perror("fork failed");
    }
    else if (pid[i] == 0) {
      for (int i = (SIZE/(temp+1))*i; i < (SIZE/(temp+1))*(i+1); i++)
      {
        tab[i]=rand() % 10001;
        if (tab[i]==42) {
          printf("indice %d = 42\n",i );
        }
      }
    }
  }


  else {
    for (int i = (SIZE/(temp+1))*(temp+1); i < SIZE; i++) {
      tab[i]=rand() % 10001;
      if (tab[i]==42) {
        printf("indice %d = 42\n",i );
      }
    }
    waitpid(pid,NULL,0);
  }
  return EXIT_SUCCESS;
}
