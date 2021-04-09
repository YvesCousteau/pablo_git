#include <string.h>

int my_strcmp(const char *s1, const char *s2);

int strcmp(const char *s1, const char *s2)
{
  return my_strcmp(s1,s2);
}

int my_strcmp(const char *s1, const char *s2)
{
  return 0;
}
