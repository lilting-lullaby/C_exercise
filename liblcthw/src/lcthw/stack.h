#ifndef lcthw_stack_h
#define lcthw_stack_h
#include <lcthw/list.h>
#define Stack List
#define Stack_create List_create
#define Stack_destroy List_destroy
#define Stack_push List_push
#define Stack_pop List_pop
#define Stack_peek List_last
#define Stack_count List_count
#define STACK_FOREACH(stack,cur) ListNode *_node = NULL;\
	ListNode *cur = NULL;\
	for(cur = _node = stack->first; _node!=NULL;cur=_node=_node->next)
#endif
