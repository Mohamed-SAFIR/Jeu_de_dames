all: f1.o main.o
	gcc -g main.o f1.o -o main.exe
liste.o : f1.c f1.h
	gcc -c -Wall -ansi -pedantic f1.c -o f1.o
main.o : f1.h main.c
	gcc -c -Wall -ansi -pedantic main.c -o main.o
