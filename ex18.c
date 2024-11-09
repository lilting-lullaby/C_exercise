#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

typedef int (*compare_cp)(int a,int b);
typedef int*(*sort_cp)(int *number , int count , compare_cp cmp);

int *sort_bubble (int *number, int count , compare_cp cmp)
{
	int i = 0;
	int j = 0;
	int temp = 0;

	for(i=0;i<count;i++){
		for(j=0;j<count-1;j++){

		if(cmp(number[j],number[j+1])>0){
		temp = number[j];
		number[j] = number[j+1];
		number[j+1] = temp;
		}

		
		}
	}
	return number;
}

int *sort_direct (int *number, int count , compare_cp cmp)
{

	int i = 0;
	int j = 0;
	int temp = 0;

	for(i=0;i<count;i++){
		for(j=i+1;j<count;j++){

		if(cmp(number[i],number[j])>0){
		temp = number[i];
		number[i] = number[j];
		number[j] = temp;
		}
	}
	}

	return number;	
}

int sorted_order(int a,int b){
	return b-a;
}
int reverse_order(int a,int b){
	return a-b;
}

void sort_test(int *number,int count,compare_cp cmp,sort_cp sort){
	sort(number,count,cmp);
	for (int i = 0;i<count;i++){
	printf("%d ",number[i]);
	}
	printf("\n");
}

int main(int argc,char *argv[]){

	int count = argc - 1;
        int *number =(int *)malloc(count*sizeof(int));
	for(int i=0;i<count;i++){
		number[i] = atoi(argv[i+1]); //char **inputs = argv+1 
	}
        sort_test(number,count,sorted_order,sort_bubble);

        sort_test(number,count,reverse_order,sort_bubble);
        sort_test(number,count,sorted_order,sort_direct);

        sort_test(number,count,reverse_order,sort_direct);

	free(number);
	return 0 ;
}
















