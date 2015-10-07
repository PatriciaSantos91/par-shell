#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include "list.h"



list_t* lst_new(){
  extern int errno;
  list_t *list;
  list = (list_t*) malloc(sizeof(list_t));
  if (list == NULL){
    fprintf(stderr,"Error on malloc: %s\n",strerror(errno));
    exit(-2);
  }
  list->first = NULL;
  list->r_sons = 0;
  return list;
}


void lst_destroy(list_t *list){
  struct lst_iitem *item, *nextitem;

  item = list->first;
  while (item != NULL){
    nextitem = item->next;
    free(item);
    item = nextitem;
  }
  free(list);
}


void insert_new_process(list_t *list, int pid, time_t starttime){
  lst_iitem_t *item;
  item = (lst_iitem_t *) malloc (sizeof(lst_iitem_t));
  if (item == NULL){
    fprintf(stderr,"Error on malloc: %s\n",strerror(errno));
    exit(-2);
  }
  item->pid = pid;
  item->starttime = starttime;
  item->endtime = 0;
  item->next = list->first;
  list->first = item;
  list->r_sons++;
}


void update_terminated_process(list_t *list, int pid, time_t endtime, int ret_int){

  lst_iitem_t * aux;
  aux = list->first;
  while(aux != NULL && aux->pid != pid){
    aux = aux->next;
  }

  aux->endtime = endtime;
  aux->ret_int = ret_int;
  list->r_sons--;
  printf("teminated process with pid: %d\n", pid);
}


void lst_print(list_t *list){	
  lst_iitem_t *item;
  printf("Process list with start, end time and return value:\n");
  item = list->first;
  while (item != NULL){
    printf("%d\t%s", item->pid, ctime(&(item->starttime)));
    printf("\t%s", ctime(&(item->endtime)));
    printf("\tReturn value:%d\n",item->ret_int);
    item = item->next;
  }
  printf("-- end of list.\n");
}