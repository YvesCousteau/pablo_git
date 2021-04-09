#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SIZE 4096

void shell_Q1(char *text);
void shell_Q2(char *text,const char *separators);
void shell_Q3(char *text,const char *separators,char *current_directory);


void separators_fct(char *text,const char *separators);
void print_input(void);
void print_input_current_directory(char *current_directory);
void print_output(char *text);

int main(int argc, char const *argv[])
{
  char text[SIZE];
  const char * separators = " ,";
  char current_directory[256];
  char question = *argv[1];
  if (getcwd(current_directory, sizeof(current_directory)) == NULL)
    perror("getcwd() error");

  switch (question) {
    case '1':
      printf("Question 1 - Selected\n");
      shell_Q1(text);
      break;
    case '2':
      printf("Question 2 - Selected\n");
      shell_Q2(text,separators);
      break;
    case '3':
      printf("Question 3 - Selected\n");
      shell_Q3(text,separators,current_directory);
      break;
    case '4':
      printf("Question 4 - Selected\n");
      break;
    case '5':
      printf("Question 5 - Selected\n");
      break;
    case '6':
      printf("Question 6 - Selected\n");
      break;
    case '7':
      printf("Question 7 - Selected\n");
      break;
    case '8':
      printf("Question 8 - Selected\n");
      break;
  }
  return 0;
}

void shell_Q1(char *text)
{
  do
  {
    print_input();
    if (fgets(text,SIZE,stdin) == NULL)
    {
      return;
    }
    print_output(text);
  }while (1);
}

void shell_Q2(char *text,const char *separators)
{
  do
  {
    print_input();
    if (fgets(text,SIZE,stdin) == NULL)
    {
      return;
    }
    separators_fct(text,separators);
  }while (1);
}

void shell_Q3(char *text,const char *separators,char *current_directory)
{
  do
  {
    print_input_current_directory(current_directory);
    if (fgets(text,SIZE,stdin) == NULL)
    {
      return;
    }
    separators_fct(text,separators);
  }while (1);
}

void separators_fct(char *text,const char *separators)
{
  char *tmp = strtok(text,separators);
    while (tmp != NULL) {
        print_output(tmp);
        tmp = strtok ( NULL, separators );
    }
}

void print_input(void)
{
  printf("mishell(ಠ_ಠ) %% \n");
}

void print_input_current_directory(char *current_directory)
{
  printf("mishell(ಠ_ಠ)[%s] %% \n",current_directory);
}

void print_output(char *text)
{
  printf("%s\n",text);
}



void command(char **arg,int nb_arg) {
  int i;
  pid_t child = fork();
  int status;
  char* tmp = NULL;

  if(child < 0)
  {
    printf("error with creating chiled process");
    return 0;
  }

  printf("Parent: %d\n", getpid());
  if(!child)
  {
    printf("Child %d\n", getpid());
    for (i = 0; i < nb_arg; i++)
    {

      if (strcmp(arg[i],"cd")==0)
      {
          chdir(arg[i+1]);
          i++;
      }
      else if (strcmp(arg[i],"exit")==0)
      {
        return;
      }
    }


  }

  waitpid(-1, &status, 0);
  printf("Parent: %d\n", getpid());


}
