#include <stdio.h>
#include <math.h>
int main()
{
	int chino[] = {1,1,4,5,1,4};
	char name[] = "Nayuta";
	char full_name[] = {'T','e','n','k','a','w','a',' ','N','y','t','a','\0'};

	printf("the size of int is : %ld\n",sizeof(int));
	printf("the size of char is : %ld\n",sizeof(char));

	printf("the size of name is : %ld\n",sizeof(name));
	printf("the size of full_name is : %ld\n",sizeof(full_name));
	printf("the size of chino is : %ld\n",sizeof(chino));
	printf("the number of name is : %ld\n",sizeof(name)/sizeof(char));
	printf("the number of full_name is : %ld\n",sizeof(full_name)/sizeof(char));
	printf("the number of full_name is : %ld\n",sizeof(full_name));
	printf("the number of name is : %ld\n",sizeof(name)/sizeof(char));
	printf("the name & full_name is \'%s\' \t & \'%s\'\n",name,full_name);

	for(int i=0;i<6;i++)
	{
	double result = (int)pow(i,i);
	chino[i] = (int) result;
        }	
 	
	name[0] = 'n';
	full_name[7] = '-';

	printf("the name & full_name is \'%s\' \t & \'%s\'\n",name,full_name);

        
	for(int i=0;i<6;i++)
	{
	printf("%d\t",chino[i]);
	}

	char *haruka = "mizumi haruka";
	printf("%s",haruka);
	



	return 0;
}
