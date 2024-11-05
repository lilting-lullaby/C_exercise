CFLAGS=-Wall -g
all: ex1 ex3 ex8 ex9 ex10

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
clean:
	rm -f ex1
	rm -f ex3
	rm -f ex8
	rm -f ex9
	rm -f ex10
