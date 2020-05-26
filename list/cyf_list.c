#include"cyf_list.h"
void __list_add(struct list_head *new,
		struct list_head *pre,
		struct list_head *nex)
{
	nex->prev = new;
	new->next = nex;
	new->prev = pre;
	pre->next = new;
}
/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}


