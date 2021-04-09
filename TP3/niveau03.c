#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


void * print(void *thread_void_ptr);

pthread_mutex_t lock;
int compteur;

int main(int argc, char const *argv[])
{

  size_t i;
  int num_thread = atoi(argv[1]);
  pthread_t threads[num_thread];
  int tmp[num_thread];
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
      perror("pthread_mutex_init() error");
      return 0;
  }
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
  pthread_mutex_destroy(&lock);

  return 0;
}

void * print(void *thread_void_ptr)
{
  pthread_mutex_lock(&lock);

  compteur ++;
  // printf("%d\n",compteur );

  pthread_mutex_unlock(&lock);
  return NULL;
}
