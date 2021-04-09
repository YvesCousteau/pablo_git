#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0
#define LOOP 10000

int main(void)
{
  fork();
  fork();
  fork();
  sleep(10);
  exit(0);
  return EXIT_SUCCESS;
}

// 2^n process with n fork (1+1+2+4+....)
//        P
//    ----F----
//  -F-     -F-
// F   F   F   F
// ...
