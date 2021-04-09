#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#define LECTURE  0
#define ECRITURE 1
#define ERROR 2

#define SIZE 4096

void shell(char *text,const char *separators);


void separators_fct(char *text,const char *separators,char **arg,int *nb_arg);
void print_input(char *current_directory);
void print_output(char *text);


void command_all(char **arg,int background_status);
int command_exit(char **arg);
int command_cd(char **arg,int nb_arg);
int command_edit_file(char **arg,int nb_arg,char* text);
int command_list(char* text,char ** arg,int nb_arg);
void command_pipe(char ** pipe_buffer,int nb_pipe,char ** arg, int nb_arg);

void pipe_fct(char ** pipe_buffer,char ** arg, int nb_arg);

#endif
