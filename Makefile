all: project2

project2: project2.o
	gcc -o project2 project2.o

project2.o: project2.c
	gcc -c -g -Wall -pedantic project2.c

clean:
	rm project2 project2.o
