#include <stdio.h>

int main()
{
	char *name = "Oyama";
	for(int i = 0 ; i<5 ; i++)
	{
		printf("name[i]:%c\n",name[i]);
	}
	

	char Harris[] = {'w','i','n','\0'};

	printf("size of Harris : %ld \n", sizeof(Harris));

	int *p = (int *)Harris; 
	
	printf("I cast the type of Harris%x\n %d\n %ld\n,%s\n", *p ,*p,sizeof(Harris),Harris);
	
        char *Harris_1 = (char *)Harris;

	printf("qwkejqkwlejlqwejqe%c\n",Harris_1[1]);
	



	return 0;
}
