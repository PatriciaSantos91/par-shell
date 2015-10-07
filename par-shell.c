#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "list.h"
#include "commandlinereader.h"


#define MAXARG 6

// Handles SIGCHLD sent by a process child, reaping him.
void handle_sigchld(int signum){
  // Reset of handler
  if (signal(SIGCHLD,handle_sigchld) == SIG_ERR){
    perror("Error on setting SIGCHLD handler");
  }

  int terminated_pid = 0, status = 0, ret_int = 0;
  time_t setTime;
/*
  terminated_pid = wait(&status);
  time(&setTime);
  if (WIFEXITED(status)){
    ret_int = WEXITSTATUS(status);
    update_terminated_process(plist, terminated_pid, setTime, ret_int);
  }
  */
}

int main(int argc, char *argv[]){
  char ** input;
  int loop = 1, cmd = 0, readVal = 0;
  int pid = 0, terminated_pid = 0, status = 0, ret_int = 0;
  list_t *plist = lst_new();
  time_t setTime;
  extern int errno;

  input = (char **) malloc(sizeof(char*)*(MAXARG));
  if (input == NULL){
    fprintf(stderr,"Error on malloc: %s\n",strerror(errno));
    exit(-1);
  }

 // Sets the SIGCHLD handler
  if (signal(SIGCHLD,handle_sigchld) == SIG_ERR){
    perror("Error on setting SIGCHLD handler");
  }

  while (loop){
    cmd = 0;
    printcmds(0);

    readVal = readLineArguments(input,MAXARG);
    if (readVal == -1)                                                        // Error on readLineArguments
      fprintf(stderr, "Error on readLineArguments: %s\n",strerror(errno));

    if (readVal > 0){
      if (strcmp(input[0],"clear") == 0){                                      // Clear cmd
        cmd = 1;
        system ( "clear" );
      }

      if (strcmp(input[0],"exit") == 0){                                      // Exit cmd
        cmd = 1;
        while(plist->r_sons > 0){
          terminated_pid = wait(&status);
          time(&setTime);
          if (WIFEXITED(status)){
            ret_int = WEXITSTATUS(status);
            update_terminated_process(plist, terminated_pid, setTime, ret_int);
          }
        loop = 0;
        }
      }

      if (!cmd){                                                  // Only runs if no cmd was invoked
        printf("Inicializing process on file %s\n", input[0]);
        pid = fork();
        if (pid < 0){
          fprintf(stderr, "Error on fork: %s\n",strerror(errno));
        }

        if (pid > 0){
          time(&setTime);
          insert_new_process(plist, pid, setTime);
        }

        if (pid == 0){
        	execv(input[0], input);
          // New program in charge, the code below runs in case an error ocurred with execv.
          fprintf(stderr,"Error on execv: %s\n",strerror(errno));
          exit(-1);
        }

      }

    }   //leitura +

  }   //loop

  lst_print(plist);
  lst_destroy(plist);
  free(input);
  printf("Exiting par-shell..\n");
  exit(7);
}