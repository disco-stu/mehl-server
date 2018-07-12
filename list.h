#include <stdlib.h>
#include <stdio.h>

#ifndef _LIST_H
#define _LIST_H

typedef struct element
{
	void 			*val;
	struct element 	*next;
} 
element_t;

element_t 	*list_create_element();
void 		 list_delete_element(element_t* e);
void 		 list_append_element(element_t *list, element_t *e);
int 		 list_remove_element(element_t *list, element_t *e);
element_t 	*list_pop(element_t *list);
int 		 list_length(element_t *list);

#endif /* _LIST_H */
