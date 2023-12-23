#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
 * @match: a member not used by linked lists but by datatypes derived 
 * 	from linked lists
 * @destroy: encapsulated destroy function passed to `list_init`
 * @head: pointer to the first linked list
 * @tail: pointer to the tail element
*/
typedef struct List_
{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy) (void *data);

	node *head;
	node *tail;
} List;


void list_init(List *list, void (*destroy)(void *data));
void list_destroy(List *list);
int list_ins_next(List *list, node *element, const void *data);
int list_rem_next(List *list, node *element, void **data);


#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list->tail))
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)


#endif /*LIST_H */