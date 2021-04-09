#include "header.h"

void command_all(char **arg,int background_status) {
  pid_t pid;
  int status;

  if ((pid = fork()) < 0)
  {
    perror("fork() error");
    return;
  }
  else if (pid == 0)
  {
    if (execvp(arg[0], arg) == -1)
    {
       perror("execvp() error");
       return;
    }
  }
  else
  {
    if (background_status == 0) {
      waitpid(pid,&status,WUNTRACED);
    }
    else
    {
      status = -1;
      waitpid(pid,&status,WNOHANG);
    }
  }
  return;
}

int command_exit(char **arg)
{
  if (strcmp(arg[0], "exit") == 0)
  {
    return -1;
  }
  return 0;
}

int command_cd(char **arg,int nb_arg)
{
  int i;
  for (i = 0; i < nb_arg; i++)
  {
    if (strcmp(arg[i],"cd") == 0)
    {
        chdir(arg[i+1]);
        i++;
        return -1;
    }
  }
  return 0;
}

int command_edit_file(char **arg,int nb_arg,char* text)
{
  int i,j;
  size_t z;
  int exit = 0;
  char ** command = NULL;
  int file_edited;
  char file[SIZE];
  int flags;
  int nb_command = 0;
  pid_t pid;
  int status;
  int checkpoint;
  int flag_dup;


  command = (char **) malloc( (nb_arg + 1) * sizeof(char *) );
  for (z = 0; z < (strlen(text) + 1); z++)
  {
    command[z] = (char *) malloc( (strlen(text) + 1) * sizeof(char) );
  }

  for (i = 0; i < nb_arg; i++)
  {
    if (((strcmp(arg[i],"<")==0) || (strcmp(arg[i],">")==0) || (strcmp(arg[i],"2>")==0)) && (arg[i+1]!=NULL))
    {
      checkpoint = i;
      exit = 1;
      for (j = 0; j < i; j++)
      {
        command[j]=arg[j];
        nb_command ++;
      }
    }
  }
  if (exit == 0) {
    return 0;
  }
  command[nb_command]=NULL;
  strcpy(file,arg[j+1]);

  if( access( file, F_OK ) == 0 )
  {
    flags = O_RDWR;
  }
  else
  {
    flags = O_CREAT | O_RDWR;
  }

  if((file_edited = open(file, flags, 0644))== -1)
  {
    perror("open() error");
    return -1;
  }

  if ((pid = fork()) < 0)
  {
    perror("fork() error");
    return -1;
  }
  else if (pid == 0)
  {
    if ((strcmp(arg[checkpoint],">")==0))
    {
      flag_dup = ECRITURE;
    }
    else if ((strcmp(arg[checkpoint],"<")==0))
    {
      flag_dup = LECTURE;
    }
    else if((strcmp(arg[checkpoint],"2>")==0))
    {
      flag_dup = ERROR;
    }

    if (dup2(file_edited, flag_dup) < 0)
    {
      perror ("dup2() error") ;
      return -1;
    }
    if (close(file_edited))
    {
      perror("close() error");
      return -1;
    }
    if (execvp(command[0], command) == -1)
    {
       perror("execvp() error");
       return -1;
    }

  }
  else
  {
    waitpid(pid,&status,WUNTRACED);
  }

  printf("\n");
  free(command);
  return 1;
}

int command_list(char* text,char ** arg,int nb_arg)
{
  if (command_exit(arg))
  {
    return -1;
  }
  else if (command_cd(arg,nb_arg))
  {
    return 0;
  }
  else if (command_edit_file(arg,nb_arg,text))
  {
    return 0;
  }
  else
  {
    command_all(arg,0);
    return 0;
  }
  return 0;
}


void command_pipe(char ** pipe_buffer,int nb_pipe,char ** arg, int nb_arg)
{
  const char * separators = " ,;";
  int pipes[10][2];
  int i = 0;
  int pid;

  nb_arg = 0;
  separators_fct(pipe_buffer[0],separators,arg,&nb_arg);

  if (pipe(pipes[0]) == -1) {
    perror("pipe() error");
    exit(1);
  }

  if ((pid = fork()) == -1)
  {
    perror("fork() error");
    exit(1);
  }
  else if (pid == 0)
  {
    dup2(pipes[0][1], 1);
    close(pipes[0][0]);
    close(pipes[0][1]);
    command_list(pipe_buffer[0],arg,nb_arg);
  }

  for (i = 0; i < nb_pipe - 2; i++)
  {
    nb_arg = 0;
    separators_fct(pipe_buffer[i+1],separators,arg,&nb_arg);

    if (pipe(pipes[i+1]) == -1)
    {
      perror("pipe() error");
      exit(1);
    }
    if ((pid = fork()) == -1)
    {
      perror("fork() error");
      exit(1);
    }
    else if (pid == 0)
    {
      dup2(pipes[i][0], 0);
      dup2(pipes[i+1][1], 1);
      close(pipes[i][0]);
      close(pipes[i][1]);
      close(pipes[i+1][0]);
      close(pipes[i+1][1]);
      command_list(pipe_buffer[i+1],arg,nb_arg);
    }
    close(pipes[i][0]);
    close(pipes[i][1]);
  }
  nb_arg = 0;
  separators_fct(pipe_buffer[i+1],separators,arg,&nb_arg);
  if ((pid = fork()) == -1)
  {
    perror("fork() error");
    exit(1);
  }
  else if (pid == 0)
  {
    dup2(pipes[nb_pipe - 2][0], 0);
    close(pipes[nb_pipe - 2][0]);
    close(pipes[nb_pipe - 2][1]);
    command_list(pipe_buffer[i+1],arg,nb_arg);
  }
}
