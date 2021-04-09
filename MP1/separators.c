#include "header.h"

void separators_fct(char *text,const char *separators,char **arg,int *nb_arg)
{
  char *tmp = strtok(text,separators);
  while (tmp != NULL)
  {
    arg[*nb_arg] = tmp;
    *nb_arg = *nb_arg + 1;
    tmp = strtok ( NULL, separators );
  }
  arg[*nb_arg] = NULL;

}
