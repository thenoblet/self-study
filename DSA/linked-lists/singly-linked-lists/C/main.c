#include "list.h"

/*
 * main - Entry point of the program.
 * 
 * This function serves as a test scenario for the linked list implementation.
 * It creates a new list, adds elements, performs operations, and prints the list.
 * Returns 0 on successful execution.
 */
int main(void)
{
	List *new_list = malloc(sizeof(List));
	if (new_list == NULL)
	{
		fprintf(stderr, "Not enough memory to continue this operation");
		exit(EXIT_FAILURE);
	}

	list_init(new_list, free_data);

	node *element1;
	if ((element1 = malloc(sizeof(node))) == NULL)
		return (1);

	int data1 = 1;
	element1->data = (void *)&data1;
	element1->next = NULL;

	if (list_size(new_list) == 0)
		new_list->tail = element1;
	
	element1->next = new_list->head;
	new_list->head = element1;
	new_list->size++;

	int data2 = 2, data3 = 3, data4 = 4;
	void *removed_data;

	char *str = "noblet";

	list_ins_next(new_list, element1 , (void *)&data2);
	list_ins_next(new_list, NULL, (void *)&data3);
	list_ins_next(new_list, NULL, (void *)str);
	list_rem_next(new_list, element1, &removed_data);

	print_list(new_list);

	list_destroy(new_list);

	return (0);
}