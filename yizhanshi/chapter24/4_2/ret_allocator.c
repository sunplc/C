/* ret_allocator.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ret_allocator.h"

unit_t *alloc_unit(void)
{
	unit_t *p = malloc(sizeof(unit_t));
	if(p == NULL) {
		printf("out of memory\n");
		exit(1);
	}
	p->number = 3;
	p->msg = malloc(20);
	strcpy(p->msg, "Are you kidding me?");
	return p;
}

void free_unit(unit_t *p)
{
	free(p->msg);
	free(p);
}
