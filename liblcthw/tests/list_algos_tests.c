#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <time.h>


char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS","sada","wsdgg","112d","sdds","uiku"};
#define NUM_VALUES 10


List *create_words()
{
    int i = 0;
    List *words = List_create();

    for(i = 0; i < NUM_VALUES; i++) {
        List_push(words, values[i]);
    }

    return words;
}

List *create_random_list()
{
	srand(time(NULL));
	int i = 0;
        List *words = List_create();
	int m = rand()%10;
	debug("M is %d",m);
	int max = rand()%100+20;
//	long long u = max;
        debug("lenth is: %d",max);	
    	for(i = 0; i < max; i++) {

	     m = rand()%10;
   	     List_push(words, values[m]);
   	     //List_push(words, u);
	    // u--;
   	 }
	return words;	
   


}

int is_sorted(List *words)
{
        LIST_FOREACH(words,first,next,cur){
	if(cur->next && strcmp(cur->value,cur->next->value)>0){
		debug("%s is large than %s",(char*)cur->value,(char*)cur->next->value);
		return 0;
	}
	}
	return 1;


}
char *test_show_time()
{	List *words = create_random_list();
	List *test1 = words;
	clock_t start, end;
	start = clock();
	debug("start is %ld",start);
	debug("lenth of words:%d",words->count);
//	int rc = List_bubble_sort(words,(List_compare)strcmp);       
//	mu_assert(rc==0,"Bubble sort failed");
	List *test = List_merge_sort(words,(List_compare)strcmp);
	int rc = is_sorted(test);
	mu_assert(rc,"fail to sort after merge_sort");
	end = clock();
	debug("end is %ld",end);
	double TIME = ((double)end-(double)start)/(double)CLOCKS_PER_SEC;
	debug("TIME is %f",TIME);
  	
	start = clock();
	debug("start is %ld",start);
	debug("lenth of words:%d",words->count);
	rc = List_bubble_sort(test1,(List_compare)strcmp);       
	mu_assert(rc==0,"Bubble sort failed");
	end = clock();
	debug("end is %ld",end);
        TIME = ((double)end-(double)start)/(double)CLOCKS_PER_SEC;
	debug("TIME is %f",TIME);
	List_destroy(words);
//	List_destroy(test1); //这俩实际上是一个链表，释放两次当场gg。报segmentatation fault

        return NULL;
}

char *test_bubble_sort()
{
	List *words = create_words();
	int rc = List_bubble_sort(words,(List_compare)strcmp);
	//printf("%d/n",rc);
	debug("The value of rc is:%d",rc );
	mu_assert(rc==0,"Bubble sort failed");
	mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");
	rc = List_bubble_sort(words,(List_compare)strcmp);	
	mu_assert(rc==0,"Bubble sort of already sorted failed");
	List_destroy(words);
	words = List_create();
	mu_assert(rc==0,"Bubble sort of filed on empty list");
	List_destroy(words);
	return NULL;
}

char *test_merge_sort()
{
	List *words = create_words();
	List *test = List_merge_sort(words,(List_compare)strcmp);
	int rc = is_sorted(test);
	mu_assert(rc,"fail to sort after merge_sort");

	List_destroy(words);
	List_destroy(test);

        return NULL;
}

char *test_insert_sorted(){
	List *words = create_random_list();
        words=List_merge_sort(words,(List_compare)strcmp);
	mu_assert(is_sorted(words),"fail to sort after merge_sort");
	debug("words count is %d",words->count);
	List_insert_sorted(words,values[1],(List_compare)strcmp);
	debug("words count is %d",words->count);
	mu_assert(is_sorted(words), "Words are not sorted after insert sort.");
	List_insert_sorted(words,values[2],(List_compare)strcmp);
	debug("words count is %d",words->count);
	mu_assert(is_sorted(words), "Words are not sorted after insert sort.");
	List_insert_sorted(words,values[3],(List_compare)strcmp);
	debug("words count is %d",words->count);
	mu_assert(is_sorted(words), "Words are not sorted after insert sort.");
	List_show(words);
	List_destroy(words);
	return NULL;
}
char *test_merge_sort_bt()
{

	List *words = create_random_list();
	words = List_merge_sort_bt(words,(List_compare)strcmp);
	mu_assert(is_sorted(words),"fail to sort after merge_sort");
	
	List_show(words);
        return NULL;

}


char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);
    mu_run_test(test_show_time);
    mu_run_test(test_insert_sorted);
    mu_run_test(test_merge_sort_bt);
    return NULL;
}

RUN_TESTS(all_tests);
