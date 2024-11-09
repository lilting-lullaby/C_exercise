#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct stack {

	int data;
};
struct Connection {
	struct stack *db;
};
struct Connection *conn;// = NULL; 
int pc = 0;
struct stack head = {0}; 
void push (int data){
	struct stack stack={data};
 	pc++;
	conn->db[pc] = stack;

}

void pop (){

  	if(pc>0){ pc--;}else {printf("pc can't be negative\n");}
}

int main()
{
	char* command;
	conn = (struct Connection*)malloc(sizeof(struct Connection));
       // memset(conn->db,0,50*sizeof(struct stack));
	conn->db = (struct stack*)malloc(50 * sizeof(struct stack));
       // memset(conn,0,sizeof(struct Connection));
	conn->db[pc] = head;
	
	printf("pc:%d data:%d\n",pc , conn->db[pc].data);
	int data = 0;	
	while(1){

	scanf("%s",command);
//	printf("command is :%s\n",command);
//        printf("%d",strcmp(command,"push"));
	if (strcmp(command,"push")==0){
		scanf("%d",&data);
		push(data);
		
		printf("pc:%d data:%d push success\n",pc , conn->db[pc].data);
	}else if(strcmp(command,"pop")==0){
	        pop();
		printf("pc:%d data:%d pop success\n",pc , conn->db[pc].data);
	}else if(strcmp(command,"exit")==0){
	 	break;
	}else{
		printf("wrong command :try it again\n");
	}
	}

	return 0;
}














