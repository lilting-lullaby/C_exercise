#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct Person{
	char *name;
	int height;
	int weight;
	int age;
	char *characterize;
};

struct Person *Person_creat(char *name,int height,int weight,int age, char *characterize){
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL); // if mallco failed,NULL will be return. 
 	who->name = strdup(name); // be care fully , the struct only sotre the pointer and value , it doesn't store the date that ptr pointing at. so you need alloc a new memory to take it.
        who->height = height;// who->height actually is *(who).height
	who->weight = weight;
	who->age = age;
	who->characterize = strdup(characterize);
	return who;
} 

struct Person Person_creat_withoutptr(char *name,int height,int weight,int age, char *characterize){
	struct Person who; 
        who.height = height;// who->height actually is *(who).height
	who.weight = weight;
	who.name = name;
	who.age = age;
	who.characterize = characterize;
	return who;
} 
void Person_destory(struct Person *who){
	assert( who!= NULL); // free multiple times will cause segemantation fault which will cause core dump.
	free(who->name);
	free(who->characterize);
	free(who); //if you woundn't free , you can use GC_malloc to alloc the memory, it will free automaticlly after you do not use it.
}

void Person_print(struct Person *who){
	printf("name:%s characterize:%s age:%d height:%d weight:%d\n",who->name,who->characterize,who->age,who->height,who->weight);
}
void Person_print_withoutptr(struct Person who){
	printf("age:%d\n",who.age);
	//printf("name:%s characterize:%s age:%d height:%d weight:%d\n",who.name,who.characterize,who.age,who.height,who.weight);
	printf("height:%d\n",who.height);
	printf("weight:%d\n",who.weight);
 
	printf("name:%s\n",who.name);
	printf("charcterize:%s\n",who.characterize);
}



int main(int argc , char *argv[]){
	
	struct Person *Oyama = Person_creat("Oyama",172,62,24,"Otaku");
        struct Person Momiji = {"Momiji",171,61,22,"Transfor"};
 	printf("Oyama is at memory location %p:\n",Oyama);
	struct Person Asahi = Person_creat_withoutptr("Asahi",166,59,23,"vanquisher");
	
 	printf("Momiji is at memory location %p:\n",&Momiji);
	Person_print(Oyama);
	printf("%d\n",Asahi.age);

	printf("%s\n",Asahi.characterize);
	Person_print_withoutptr(Asahi);
	Person_destory(Oyama);

	return 0;

}
























