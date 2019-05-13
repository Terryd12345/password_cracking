all: main.c functions.h
	gcc -Wall main.c -o crack

dh: dh.c functions.h
	gcc -Wall dh.c -lm -o dh