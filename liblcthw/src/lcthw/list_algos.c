#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>


int List_bubble_sort(List *list, List_compare cmp)
{
	int sort = 1;
	debug("the lenth of list is: %d",list->count);
	if(list->count <=1){
	return 0;
	}
	void* temp = NULL; 
	while(sort){
		sort = 0;
		LIST_FOREACH(list,first,next,cur){
		if(cur->next){
			if(cmp(cur->value,cur->next->value)>0){
				temp = cur->next->value;
				cur->next->value = cur->value;     //change order
				cur->value = temp;
				sort = 1;
//				debug("sort is : %d",sort);
			}
		}
	}
	}	
	debug("the value of sort:%d",sort);
	return 0;
	
}

inline List *List_merge(List *left, List *right, List_compare cmp)
{

	List *result = List_create();
	void *val =NULL;
	while (right->count>0 || left->count>0){
		if(right->count>0 && left->count>0){
			if(cmp(List_first(right),List_first(left))>=0){
				val = List_shift(left);	
			 }else{
				val = List_shift(right);
			}
			List_push(result,val);
		} else if(right->count>0){
			val = List_shift(right);
			List_push(result,val);
		} else if(left->count>0){
			val = List_shift(left);
			List_push(result,val);
		}
	}
	return result;
}


List *List_merge_sort(List *list, List_compare cmp)
{
	if(list->count<=1){
		 return list;
	}
	List *left = List_create();
	List *right = List_create();
	int middle = list->count/2;//舍弃小数部分，若count为3,则左侧两个右侧1个。
	LIST_FOREACH(list,first,next,cur)
	{
		if(middle>0){
			List_push(right,cur->value);
		}else {
			List_push(left,cur->value);
		}
		middle--;
	}
	
	List *sort_left = List_merge_sort(left,cmp);
	List *sort_right = List_merge_sort(right,cmp);
	if(sort_left != left) List_destroy(left);
        if(sort_right != right) List_destroy(right);
	
	return List_merge(sort_left,sort_right,cmp);

}


List *List_insert_sorted(List *list,void *value,List_compare cmp)
{
	if(!list->first){
		List_unshift(list,value);
		return list;
	}
	debug("THE value is :; %s",value);
        debug("THE list count is %d in insert_sorted",list->count);	
	if(cmp(list->first->value,value)>=0){
		List_unshift(list,value);
	}else if(cmp(list->last->value,value)<=0){
		List_push(list,value);
	}else {
		LIST_FOREACH(list,first,next,cur){
			if(cur->next){
				if(cmp(cur->value,value)<=0&&cmp(cur->next->value,value)>=0){
						ListNode *node = calloc(1,sizeof(ListNode));
						check_mem(node);
						node->value = value;
						node->next = cur->next;
						node->prev = cur;
						cur->next->prev = node;
						cur->next = node;
						list->count++;
						return list;// 一定要及时加入这个,不然会导致插入后仍在遍历，一直插入从而导致一直插入节点。
												
				}	
			
			}
		}
	
	}
	
	return list;
error:
	debug("fail to alloc memory");
	return list;
	
}

ListNode *merge_nd(ListNode *left,ListNode *right,List_compare cmp)
{	
	List *result = List_create();
	ListNode *next;
	while(left!=NULL || right != NULL ){
		if(left!=NULL && right != NULL){
			if(cmp(left->value,right->value)>=0){
				next = right->next;
				right->next = NULL;
				List_push(result,right->value);	
				right = next;
			} else{
				next = left->next;
				left->next = NULL;
				List_push(result,left->value);
				left = next;
			}
		}else if (left==NULL && right!= NULL){
			
			next = right->next;
			right->next = NULL;
			List_push(result,right->value);	
			right = next;
		}else if (left != NULL && right == NULL){
			next = left->next;
			left->next = NULL;
			List_push(result,left->value);
			left = next;

		}		
	
	}

	debug("COUNT OF LIST IS %d",result->count);
	return result->first;


}



List *List_merge_sort_bt(List *list, List_compare cmp)
{
	
	List *test = List_create();
	if(!list->first){
		return list;
		}
	ListNode *array[32] = {NULL};
	ListNode *next;
	ListNode *result;
	int i = 0;
	result = list->first;
	while(result){
		next = result->next;	
		result->next = NULL;
		for (i=0; (i<32) && (array[i]!=NULL);i++)
		{
			result = merge_nd(array[i],result,cmp);
			array[i]= NULL;
		}
		if(i==32) i=i-1;
		array[i]=result;
		result = next; 
			
	}
	for(i=0;i<32;i++){
		result = merge_nd(array[i],result,cmp);
	}
	while(result){
		next = result->next;
		result->next = NULL;
		List_push(test,result->value);
		result = next;	
	}
	return test;

	
}




