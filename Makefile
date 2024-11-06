CFLAGS=-Wall -g
all: ex1 ex3 ex8 ex9 ex10 ex13 ex13_1 ex14 ex15
ex3: ex3.c
	gcc -o ex3 ex3.c
ex1: ex1.c
	gcc -o ex1 ex1.c
ex8: ex8.c
	gcc -o ex8 ex8.c -lm
ex9: ex9.c
	gcc -o ex9 ex9.c
ex10: ex10.c
	gcc -o ex10 ex10.c
ex13: ex13.c
	gcc -o ex13 ex13.c
ex13_1: ex13_1.c
	gcc -o ex13_1 ex13_1.c
ex14: ex14.c
	gcc -o ex14 ex14.c
ex15: ex15.c
	gcc -g -o ex15 ex15.c
clean:
	rm -f ex1
	rm -f ex3
	rm -f ex8
	rm -f ex9
	rm -f ex10
	rm -f ex13
	rm -f ex13_1
	rm -f ex14
	rm -f ex15
