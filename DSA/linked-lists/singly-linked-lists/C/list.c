#include "list.h"

/*
 * list_init - Initializes a linked list.
 * @list: Pointer to the List structure to be initialized.
 * @destroy: Pointer to the function that will be used to free
 *           the memory of each element when the list is destroyed.
 *
 * This function initializes the linked list by setting its size to 0,
 * specifying the destroy function, and setting head and tail pointers to NULL.
 */
void list_init(List *list, void (*destroy)(void *data))
{
	/* initialise the list */
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}

/*
 * list_destroy - Destroys a linked list.
 * @list: Pointer to the List structure to be destroyed.
 *
 * This function iterates through the linked list, removes each element,
 * and frees the memory associated with the list. If a destroy function is
 * provided, it is used to free the memory of each element.
 */
void list_destroy(List *list)
{
	void *data = NULL;

	while (list_size(list) > 0)
	{
		if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL)
			//list->destroy(data);
			;
	}

	_free((void **)&list);
	return;
}

/*
 * list_ins_next - Inserts a new element after the specified element.
 * @list: Pointer to the List structure.
 * @element: Pointer to the element after which the new element will be inserted.
 * @data: Pointer to the data that will be stored in the new element.
 *
 * This function inserts a new element containing the specified data after
 * the specified element in the linked list. If the element is NULL, the new
 * element is inserted at the beginning of the list.
 * Returns 0 on success, -1 on failure.
 */
int list_ins_next(List *list, node *element, const void *data)
{
	node *new_node;

	if ((new_node = malloc(sizeof(node))) == NULL)
		return (-1);
	
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

/*
 * list_rem_next - Removes the element after the specified element.
 * @list: Pointer to the List structure.
 * @element: Pointer to the element before the one to be removed.
 * @data: Pointer to a pointer that will store the data of the removed element.
 *
 * This function removes the element after the specified element in the linked list.
 * If the element is NULL, the element at the head of the list is removed.
 * Returns 0 on success, -1 on failure.
 */
int list_rem_next(List *list, node *element, void **data)
{
	node *old_element;

	/* removal from empty list is not allowed */
	if (list_size(list) == 0)
		return (-1);
	
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
		/* removal from somewhere other than the head of the list */
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

/*
 * print_list - Prints the data of each element in the linked list.
 * @list: Pointer to the List structure.
 *
 * This function prints the data of each element in the linked list,
 * either as a string or an integer, depending on the type of data.
 * Returns the number of nodes in the list.
 */
size_t print_list(List *list)
{
	size_t node_count = 0;

	/* Start from the head of the list */
	const node *current = list->head;

	while (current != NULL)
	{
		if (list_size(list) > 0)
		{
			/* Determine the type of data and print accordingly */
			if (_isword((char *)(current->data)))
				printf("Data [%zu]: %s\n", node_count, ((char *)(current->data)));
			else
				printf("Data [%zu]: %d\n", node_count, *((int *)(current->data)));
			
			/* Increment the node count and move to the next element */
			node_count++;
			current = current->next;
		}
	}
	return (node_count);
}

/*
 * _free - Frees the memory allocated for a pointer and sets it to NULL.
 * @ptr: Pointer to the pointer whose memory needs to be freed.
 *
 * This function frees the memory allocated for the pointer if it is not NULL,
 * and then sets the pointer to NULL to avoid any potential dangling pointers.
 */
void _free(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/*
 * free_data - Frees the memory allocated for data.
 * @data: Pointer to the data whose memory needs to be freed.
 *
 * This function frees the memory allocated for the data if it is not NULL.
 */
void free_data(void *data)
{
	if (data != NULL)
	{
		free(data);

	}
}

/*
 * _isword - Checks if the given string consists of alphabetical characters.
 * @data: Pointer to the string to be checked.
 *
 * This function checks if the provided string consists only of alphabetical characters.
 * Returns 1 if it is a word, 0 otherwise.
 */
int _isword(const char *data)
{
	if (data == NULL)
	{
		fprintf(stderr, "string is empty");
		exit(EXIT_FAILURE);		
	}

	for (size_t i = 0; data[i] != '\0'; ++i)
	{
		if (!isalpha(data[i]))
			return (0);
	}
	return (1);
}