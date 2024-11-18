#ifndef lcthw_queue_h
#define lcthw_queue_h
#include <lcthw/list.h>
#define Queue List
#define Queue_create List_create
#define Queue_destroy List_destroy
#define Queue_recv List_pop
#define Queue_send List_unshift
#define Queue_peek List_last
#define Queue_count List_count
#define QUEUE_FOREACH(stack,cur) ListNode *_node = NULL;\
	ListNode *cur = NULL;\
	for(cur = _node = stack->first; _node!=NULL;cur=_node=_node->next)
#endif
