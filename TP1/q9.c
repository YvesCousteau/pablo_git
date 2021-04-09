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

  for (int i = 0; i < SIZE; i++) {
    tab[i]=rand() % 10001;
    if (tab[i]==42) {
      printf("indice %d = 42\n",i );
    }
  }
  return EXIT_SUCCESS;
}
