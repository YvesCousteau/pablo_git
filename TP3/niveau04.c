#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>



void * prod(void *thread_void_ptr);
void * conso(void *thread_void_ptr);
pthread_mutex_t lock;
int lifo_size = 100;
int lifo[100];

// int conso = atoi(argv[2]);
// int prod = atoi(argv[3]);
sem_t semaphore;
int lifo_pos = 0;
int obj = 0;

int main(int argc, char const *argv[])
{
  size_t i;
  pthread_t threads[2];
  int max_obj = atoi(argv[1]);
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
      perror("pthread_mutex_init() error");
      return 0;
  }

  if (pthread_create(&threads[0], NULL, prod, &max_obj))
  {
    perror("pthread_create() error");
    return 0;
  }
  if (pthread_create(&threads[1], NULL, conso, &max_obj))
  {
    perror("pthread_create() error");
    return 0;
  }
  for (i = 0; i < 2; i++)
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

void * conso(void *thread_void_ptr)
{
  int *num = (int *)thread_void_ptr;
  int max_obj = num[0];
  while (obj < max_obj)
  {
    printf("ok\n");
    while(lifo_pos <= 0)
    {
      sem_wait(&semaphore);
    }
    pthread_mutex_lock(&lock);
    printf("ca conso\n");
    lifo[lifo_pos]=-1;
    lifo_pos --;
    pthread_mutex_unlock(&lock);
    sem_post(&semaphore);
  }

}

void * prod(void *thread_void_ptr)
{
  int *num = (int *)thread_void_ptr;
  int max_obj = num[0];
  printf("%d\n",max_obj );
  printf("%d\n",obj );
  while (obj < max_obj)
  {
    printf("ok___\n");
    while (lifo_pos >= lifo_size-1)
    {
      sem_wait(&semaphore);
    }
    pthread_mutex_lock(&lock);
    printf("ca prod\n");
    lifo[lifo_pos]= obj;
    lifo_pos ++;
    obj ++;
    pthread_mutex_unlock(&lock);
    sem_post(&semaphore);
  }
}
