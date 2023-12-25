#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * struct node_ - represents individual elements of a linked list
 * 
 * @data: a data member of the struct 
 * @next: pointer to the next element in the list.
*/
typedef struct node_
{
	void *data;
	struct node_ *next;
} node;

/**
 * struct List_ - a linked list data structure
 * 
 * @size: number of elements in the list
 * @destroy: encapsulated destroy function passed to `list_init`
 * @head: pointer to the first linked list
 * @tail: pointer to the tail element
*/
typedef struct List_
{
	int size;
	void (*destroy)(void *data);

	node *head;
	node *tail;
} List;

/* list manipulation functions */
void list_init(List *list, void (*destroy)(void *data));
void list_destroy(List *list);
void _free(void **ptr);
void free_data(void *data);
int list_ins_next(List *list, node *element, const void *data);
int list_rem_next(List *list, node *element, void **data);
size_t print_list(List *list);

/* string functions */
int _isword(const char *data);


/* macros */
#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)


#endif /*LIST_H */