#include "header.h"

void shell(char *text,const char *separators)
{
  char current_directory[SIZE];
  int i;
  size_t z;
  int nb_arg;
  int nb_pipe = 0;
  char ** arg = NULL;
  char ** pipe_buffer = NULL;
  const char * pipe_separators = "|";
  char * background_separators = " ,;&";
  int pipe_statuts=0;
  int background_statuts=0;

  arg = (char **) malloc( (strlen(text) + 1) * sizeof(char *) );
  for (z = 0; z < (strlen(text) + 1); z++)
  {
    arg[z] = (char *) malloc( (strlen(text) + 1) * sizeof(char) );
  }

  pipe_buffer = (char **) malloc( (strlen(text) + 1) * sizeof(char *) );
  for (z = 0; z < (strlen(text) + 1); z++)
  {
    pipe_buffer[z] = (char *) malloc( (strlen(text) + 1) * sizeof(char) );
  }


  if (getcwd(current_directory, sizeof(current_directory)) == NULL)
    perror("getcwd() error");
  do
  {
    for (z = 0; z < (strlen(text) + 1); z++)
    {
      arg[z] = NULL;
    }
    for (z = 0; z < (strlen(text) + 1); z++)
    {
      pipe_buffer[z] = NULL;
    }

    print_input(current_directory);
    if (fgets(text,SIZE,stdin) == NULL)
    {
      return;
    }
    nb_pipe = 0;
    nb_arg = 0;
    pipe_statuts = 0;

    if (text[strlen(text)-1] == '\n')
    {
      text[strlen(text)-1] = '\0';
    }

    for (z = 0; z < strlen(text) + 1; z++)
    {
      if (text[z] == '|')
      {
        pipe_statuts = 1;
      }
      if (text[z] == '&')
      {
        background_statuts = 1;
      }
    }

    if (pipe_statuts == 1)
    {

      separators_fct(text,pipe_separators,pipe_buffer,&nb_pipe);
      /* command_pipe(pipe_buffer,nb_pipe,arg,nb_arg); */
      pipe_fct(pipe_buffer,arg,nb_arg);
    }
    else if (background_statuts == 1)
    {
      separators_fct(text,background_separators,arg,&nb_arg);
      command_all(arg,background_statuts);
    }
    else
    {
      separators_fct(text,separators,arg,&nb_arg);

      if (command_list(text,arg,nb_arg) == -1)
      {
        return;
      }
    }

    if (getcwd(current_directory, sizeof(current_directory)) == NULL)
      perror("getcwd() error");
  }while (1);

  for (i = 0; i < nb_arg; i++) {
    free(arg[i]);
  }
  free(arg);
  for (i = 0; i < nb_pipe; i++) {
    free(pipe_buffer[i]);
  }
  free(pipe_buffer);
}
