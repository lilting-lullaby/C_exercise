#include <stdio.h>

int main(int argc , char *argv[])
{
	int i,j;
	for ( i =0, j = 10; i<5 && j>0; i++ ,j--)
	{
		printf("i = %d,j = %d\n",i,j);
	}

	char *state[] = {"Chino","Furukawa","Kakeniwa",NULL};

	printf("the fourth element of state is %s:\n", state[3]);
	argv[0] = state[2];
	printf("the first element of argv is %s:\n", argv[0]);

	state[0] = argv[0] ;
	printf("the first element of state is %s:\n", state[0]);
	

        int m = 3;

	while(m>=0)
	{
		printf("the %d numer of state[] is %s\n", m , state[m]);
		argv[m] = state[m];
		printf("the %d numer of argv[] is %s\n", m , argv[m]);

		printf("the adress of state[] & argv[] is %p  %p\n",(void*)&state[m],(void*)&argv[m]);
		m--;
	}


	return 0;

}
