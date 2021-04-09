#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


void * print(void *thread_void_ptr);

int compteur;

int main(int argc, char const *argv[])
{
  size_t i;
  int num_thread = atoi(argv[1]);
  pthread_t threads[num_thread];
  int tmp[num_thread];
  for (i = 0; i < num_thread; i++)
  {
    tmp[i]=i;
    if (pthread_create(&threads[i], NULL, print, &tmp[i]))
    {
      perror("pthread_create() error");
      return 0;
    }

  }
  for (i = 0; i < num_thread; i++)
  {
    if(pthread_join(threads[i], NULL))
    {
      perror("pthread_join() error");
      return 0;
    }

  }

  return 0;
}

void * print(void *thread_void_ptr)
{
  compteur ++;
  // printf("%d\n",compteur );
}
