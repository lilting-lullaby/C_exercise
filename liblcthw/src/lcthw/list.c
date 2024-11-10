#include <stdlib.h>
#include <lcthw/dbg.h>
#include <lcthw/list.h>

List *List_create(){
	return (List*)calloc(1,sizeof(List));
}

void List_destroy(List *list){

	LIST_FOREACH(list,first,next,cur){ //amazing 
		if(cur->prev){
			free(cur->prev);
		}

	}
	free(list->last);
	free(list);
}

void List_clear(List *list){

	LIST_FOREACH(list,first,next,cur){
		if(cur->value){
			free(cur->value);
			cur->value = NULL;
		}
	}

}

void List_clear_destroy(List *list){
	List_clear(list);
	List_destroy(list);
}

void List_push(List *list, void *value){

	ListNode *node = calloc(1,sizeof(ListNode));
	check_mem(node);
	node->value = value;
	if(list->last==NULL){
		list->first = node;
		list->last = node; // when you inset the first node to a list, it is the first as well as the last node.
	}else {
		list->last->next = node;
		node->prev = list->last;;
		list->last=node;
	}
	list->count++;
error:
	return;

}

void *List_pop(List *list){

	ListNode *node = list->last;
	return node!=NULL?List_remove(list,node):NULL;
//	void *value = List_last(last);
//	free(list->last->prev->next);
//	list->last->prev->next = NULL;
//	list->last = list->last->prev;
//	return value; 
}
void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list,ListNode *node){
	void *result = NULL;
        check(list->last && list->first,"List is empty");
	check(node,"Node is empty");
	if(node == list->first && node == list->last){
		list->first = NULL;
		list->last = NULL;
	}else if(node == list->last){
		list->last = node->prev;
		check(list->last!=NULL,"Invild list");
		list->last->next = NULL;
	}else if(node == list->first){
		list->first = node->next;
		check(list->first!=NULL,"Invild list");
		list->first->prev = NULL;
	}else{
		ListNode *after = node->next;
		ListNode *before = node->prev;
		after->prev = before;
		before->next = after;
	}
	list->count--;
	result = node->value;
	return result;
	free(node);

error:
	return result;	
}


















































