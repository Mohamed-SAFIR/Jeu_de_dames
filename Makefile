all: jeu.o main.o
	gcc -g main.o jeu.o -o main.exe
liste.o : jeu.c jeu.h
	gcc -c -Wall -ansi -pedantic jeu.c -o jeu.o
main.o : jeu.h main.c
	gcc -c -Wall -ansi -pedantic main.c -o main.o

