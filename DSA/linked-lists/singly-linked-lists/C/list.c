#include "list.h"

void list_init(List *list, void (*destroy)(void *data))
{
	/* initialise the list */

	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}


void list_destroy(List *list)
{
	void *data;

	while (list_size(list) > 0)
	{
		if (list_rem_next(list, NULL, (void**)&data) == 0 && list->destroy != NULL)
		{
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(list));
	return;
}

int list_ins_next(List *list, node *element, const void *data)
{
	node *new_node;

	if (new_node == malloc(sizeof(node)) == NULL)
		return (1);
	
	new_node->data = (void *)data;
	if (element == NULL)
	{
		if (list_size(list) == 0)
			list->tail = new_node;
		
		new_node->next = list->head;
		list->head = new_node;
	}
	else
	{
		if (element->next == NULL)
			list->tail = new_node;
		
		new_node->next = element->next;
		element->next = new_node;
	}

	list->size++;
	return (0);

}

int list_rem_next(List *list, node *element, void **data)
{
	node *old_element;

	/* removal from empty list is not allowed */
	if (list_size(list) == 0)
		return (1);
	
	/* removal from head of the list */
	if (element == NULL)
	{
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(list) == 1)
			list->tail = NULL;
	}
	else
	{
		/* removal from somewhere other than the list */
		if (element->next == NULL)
			return (-1);
		
		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		if (element->next == NULL)
			list->tail = element;
	}
	/* free the memory alloc'd for the abstract datatype */
	free(old_element);
	list->size--;
	return (0);
}