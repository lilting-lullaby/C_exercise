#include <stdio.h>
#include <ctype.h>
#include <string.h>
// forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);

void print_arguments(int argc, char *argv[])
{
    int i = 0;
    
    for(i = 0; i < argc; i++) {
	int lenth = strlen(argv[i]);
	printf("the lenth of argv[%d] is %d\n",i,lenth);
        print_letters(argv[i]);
    }
}

void print_letters(char arg[])
{
    int i = 0;

    for(i = 0; arg[i] != '\0'&& i < 5; i++) {
        char ch = arg[i];

        if(isalpha(ch)||isblank(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}



int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}


