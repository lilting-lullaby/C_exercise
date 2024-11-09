#include <stdio.h>

int main (int argc , char *argv[])
{

	for (int i = 1 ; argv[i]!= NULL ; i++)
	{

		for (int m = 0 ; argv[i][m] != '\0';m ++)
		{
		char letter = argv[i][m];

		switch(letter){
			case 'A':
				argv[i][m] = 'a';
				printf("SUCCESS");
				break;

			case 'B':
				argv[i][m] = 'b';
				printf("SUCCESS");
				break;
		
			case 'C':
				argv[i][m] = 'c';
				printf("SUCCESS");
				break;
		
			case 'D':
				argv[i][m] = 'd';
				printf("SUCCESS");
				break;
			case 'E':
				argv[i][m] = 'e';
				printf("SUCCESS");
				break;
			case 'F':
				argv[i][m] = 'f';
				printf("SUCCESS");
				break;
			case 'G':
				argv[i][m] = 'g';
				printf("SUCCESS");
				break;
			case 'H':
				argv[i][m] = 'h';
				printf("SUCCESS");
				break;
			case 'I':
				argv[i][m] = 'i';
				printf("SUCCESS");
				break;
			case 'J':
				argv[i][m] = 'j';
				printf("SUCCESS");
				break;
			case 'K':
				argv[i][m] = 'k';
				printf("SUCCESS");
				break;
			case 'L':
				argv[i][m] = 'l';
				printf("SUCCESS");
				break;
			case 'M':
				argv[i][m] = 'm';
				printf("SUCCESS");
				break;
			case 'N':
				argv[i][m] = 'n';
				printf("SUCCESS");
				break;
			case 'O':
				argv[i][m] = 'o';
				printf("SUCCESS");
				break;
			case 'P':
				argv[i][m] = 'p';
				printf("SUCCESS");
				break;
			case 'Q':
				argv[i][m] = 'q';
				printf("SUCCESS");
				break;
			case 'R':
				argv[i][m] = 'r';
				printf("SUCCESS");
				break;
			case 'S':
				argv[i][m] = 's';
				printf("SUCCESS");
				break;
			
		}
		
	
		
		}
		printf("\n%s\n",argv[i]);




	}
		
	for (int n = 1 ; argv[n]!= NULL ; n++){
		printf("%s ",argv[n]);
	}

	return 0;
}
