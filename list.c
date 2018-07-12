/* filename: list.c  */

#include "list.h"

element_t *list_create_element()
{
	element_t 	*e;
	
	e = malloc(sizeof(element_t));
	if(0 == e) 
	{
		perror("malloc");
		return 0;
	}
	
	e->next = 0;

	return e;
}

void list_delete_element(element_t *e)
{
	free(e);

	return;
}

void list_append_element(element_t *list, element_t *e)
{
	element_t 	*cur = list;

	while(0 != cur->next)
		cur = cur->next;

	cur->next = e;

	return;
}

int list_remove_element(element_t *list, element_t *e)
{
	element_t 	*cur = list;

	while(cur->next != e || cur->next == 0)
		cur = cur->next;

	if(0 == cur->next)
		return -1;

	if(cur->next->next != 0)
		cur->next = cur->next->next;
	
	return 0;
}

element_t *list_pop(element_t *list)
{
	element_t 	*cur = list,
				*e 	 = list;

	if( (0 != cur->next) )
	{
		while( cur->next->next != 0 )
			cur = cur->next;

		e = cur->next;
	}

	cur->next = 0;

	return e;
}

int list_length(element_t* list)
{
	int 		 length = 1;
	element_t 	*cur  	= list;

	while(cur->next != 0)
	{
		cur = cur->next;
		length++;
	}

	return length;
}
