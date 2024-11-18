#ifndef lcthw_List_algos_h
#define lcthw_List_algos_hi
#include <lcthw/list.h>


typedef int (*List_compare)(const void *a, const void *b);


int List_bubble_sort(List *list,List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);
List *List_insert_sorted(List *list,void* value,List_compare cmp);
List *List_merge_sort_bt(List *list ,List_compare cmp);
#endif
