#include "header.h"

 void pipe_fct(char ** pipe_buffer,char ** arg, int nb_arg)
 {
   int fd[2];
   pid_t pid;
   int fd_in = 0;
   int i;
   int j;
   const char * separators = " ,;";
   int status_edit;
   int file_edited;
   char file[SIZE];

   i = 0;
   while (pipe_buffer[i] != NULL)
   {
     status_edit = -1;

     nb_arg = 0;
     separators_fct(pipe_buffer[i],separators,arg,&nb_arg);

     for (j = 0; j < nb_arg; j++)
     {
       if ((strcmp(arg[j],"<")==0) || (strcmp(arg[j],">")==0) || (strcmp(arg[j],"2>")==0))
       {
         if (strcmp(arg[j],"<")==0)
         {
           status_edit = LECTURE;
         }
         else if (strcmp(arg[j],">")==0)
         {
           status_edit = ECRITURE;
         }
         else if (strcmp(arg[j],"2>")==0)
         {
           status_edit = ERROR;
         }
         strcpy(file,arg[j+1]);
         arg[j] = NULL;
         arg[j+1] = NULL;
         nb_arg = nb_arg - 2;

         if((file_edited = open(file, O_CREAT | O_RDWR))== -1)
         {
           perror("open() error");
         }
       }
     }
     pipe(fd);
     if ((pid = fork()) == -1)
     {
       perror("fork() error");
       exit(1);
     }
     else if (pid == 0)
     {
       dup2(fd_in,0);
       if (pipe_buffer[i+1]!= NULL)
       {
         dup2(fd[1],1);
       }
       close(fd[0]);

       if (status_edit != -1)
       {
         if (dup2(file_edited, status_edit) < 0)
         {
           perror ("dup2() error") ;
         }
         if (close(file_edited))
         {
           perror("close() error");
         }
       }

       if (execvp(arg[0], arg) == -1)
       {
          perror("execvp() error");
       }
     }
     else
     {
       wait(NULL);
       close(fd[1]);
       fd_in = fd[0];
       i++;
     }
   }
 }
