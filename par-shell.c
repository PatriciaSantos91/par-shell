#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include "list.h"
#include "commandlinereader.h"


#define MAXARG 6

int main(int argc, char *argv[]){

  char ** argmts;
  int i = 0, loop = 1, readVal = 0;
  int new_son;
  plist = lst_new();
  time_t = start_time;
  extern int errno;

  argmts = (char **) malloc(sizeof(char*)*(MAXARG));
  if (argmts == NULL){
    printf("Error on malloc: %s\n",strerror(errno));
    exit(3);
  }

  while (loop){
    printcmds(0);
    readVal = readLineArguments(argmts,MAXARG);
    if (readVal == -1)                                                         // Error on readLineArguments
      printf("Error on readLineArguments: %s\n",strerror(errno));

    if (readVal > 0){
      if (strcmp(argmts[0],"clear") == 0)                                      // Clear cmd
        system ( "clear" );

      if (strcmp(argmts[0],"exit") == 0){                                      // Exit cmd
        printf("Exiting par-shell..\n");
        loop = 0;
      }else{
        printf("Iniciando processo %s\n", argmts[0]);
        insert_new_process(plist, int new_son, start_time);


    }
  }

  //lst_destroy(plist);
  exit(7);
}