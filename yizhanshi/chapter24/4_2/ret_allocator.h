/* ret_allocator.h */
#ifndef RET_ALLOCATOR_H
#define RET_ALLOCATOR_H

typedef struct {
	int number;
	char *msg;
} unit_t;

extern unit_t *alloc_unit(void);
extern void free_unit(unit_t *);

#endif
