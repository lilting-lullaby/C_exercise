#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("you need one arguments\n");
		
		return 1;

	}

	for(int i = 0; argv[1][i] != '\0';i++)
	{
		switch(argv[1][i])
		{
			case'O': 
				argv[1][i] = 'A';
				printf(" %c has replaced the argc[%d]\n",argv[1][i],i);
				break;	
			case'y': 
				argv[1][i] = 's';
	
				printf(" %c has replaced the argc[%d]\n",argv[1][i],i);
				break;	
			case'a':
			        if(i == 2){	
				argv[1][i] = 'a';
				printf(" %c has replaced the argc[%d]\n",argv[1][i],i);
				}
				else{
				argv[1][i] = 'i';
				printf(" %c has replaced the argc[%d]\n",argv[1][i],i);
				}	
				break;	
			case'm': 
				argv[1][i] = 'h';
	
				printf(" %c has replaced the argc[%d]\n",argv[1][i],i);
				break;	
			default:
				printf("argc[%d] does't be changed\n",i);
		}

	}
	printf("%s\n",argv[1]);
	return 0;
}
