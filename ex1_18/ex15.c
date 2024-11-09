#include <stdio.h>

void direct(int array[], char *name[], int sizeof_array ){
	int *p_array = array;
	char **p_name = name; 

	for(int i = 0 ;i < sizeof_array;i++){
		printf("%d  %d %d %d\b\n",array[i],p_array[i],*(array+i),*(p_array+i));
	}
	int count = 0; 
	while(name[count]!=NULL){
		printf("%s %s %s %s \n",name[count],p_name[count],*(name+count),*(p_name+count));
		count++;
	}
}


int main (int argc, char *argv[])
{
	int age[] = {32,35,21,65,123};
	char *name[] = {"Oyama","Asahi","Nayuta","Miyo","Momiji",NULL};

	for(int i = 0; i<5;i++)
	{
		printf("%s : %d\n",name[i],age[i]);
	}
	
	int *p_age = age;
	char **p_name = name;

	for(int i = 0; i<5;i++)
	{
		printf("%s : %d\n",*(p_name+i),*(p_age+i));
	}


	for(int i = 0; i<5;i++)
	{
		printf("%s : %d\n",*(name+i),*(age+i));
	}

	for(int i = 0; i<5;i++)
	{
		printf("%s : %d\n",p_name[i],p_age[i]);
	}

	for(int i = sizeof(age)/sizeof(int)-1;i>=0;i--)
	{
		printf("%d element is : %d\n", i , age[i]);

	}

        char **command = argv;

	for(int i = 0 ; i < argc; i++)
	{
		printf("%d element is : %s\n", i , *(command+i));

	}
	
	for(int i = 0 ; i < argc; i++)
	{
		printf("%d element is : %s & the %p\n ", i , argv[i],argv[i]);

	}
        int sizeof_array = sizeof(age)/sizeof(int);
	direct(age,name,sizeof_array);






	return 0;
}
