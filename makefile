all: main.c
	gcc main.c -o crack

test: sha256_test.c sha256.h sha256.c
	gcc sha256_test.c -o test