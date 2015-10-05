#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "list.h"



list_t* lst_new(){
  list_t *list;
  list = (list_t*) malloc(sizeof(list_t));
  if (list == NULL) {
    printf("No memory avaiable for malloc.\n");
    exit(-2);
  }
  list->first = NULL;
  list->n_sons = 0;
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
    printf("No memory avaiable for malloc.\n");
    exit(-2);
  }
  item->pid = pid;
  item->starttime = starttime;
  item->endtime = 0;
  item->next = list->first;
  list->first = item;
  list->n_sons++;
}


void update_terminated_process(list_t *list, int pid, time_t endtime){

  lst_iitem_t * aux;
  aux = list->first;
  while(aux != NULL && aux->pid != pid){
    aux = aux->next;
  }

  aux->endtime = endtime;
  list->n_sons--;
  printf("teminated process with pid: %d\n", pid);
}


void lst_print(list_t *list){	
  lst_iitem_t *item;
  printf("Process list with start and end time:\n");
  item = list->first;
  while (item != NULL){
    printf("%d\t%s", item->pid, ctime(&(item->starttime)));
    printf("\t%s", ctime(&(item->endtime)));
    item = item->next;
  }
  printf("-- end of list.\n");
}