#ifndef _LIST_H_
#define _LIST_H_

/* lst_iitem - each element of the list points to the next element */
// ret_int -> stores the int value returned by exit()
typedef struct lst_iitem {
  int pid;
  int ret_int;
  time_t starttime;
  time_t endtime;
  struct lst_iitem *next;
} lst_iitem_t;

/* list_t */
// r_ sons: Stores the number of sons currently running
typedef struct {
  lst_iitem_t * first;
  int r_sons;												
} list_t;



/* lst_new - allocates memory for list_t and initializes it */
list_t* lst_new();

/* lst_destroy - free memory of list_t and all its items */
void lst_destroy(list_t *);

/* insert_new_process - insert a new item with process id and its start time in list 'list' */
void insert_new_process(list_t *list, int pid, time_t starttime);

/* lst_remove - remove first item of value 'value' from list 'list' */
void update_terminated_process(list_t *list, int pid, time_t endtime, int ret_int);

/* lst_print - print the content of list 'list' to standard output */
void lst_print(list_t *list);


#endif