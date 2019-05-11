all: main.c functions.h
	gcc main.c -o crack

dh: dh.c functions.h
	gcc dh.c -lm -o dh