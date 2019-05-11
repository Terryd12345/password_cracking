/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Performs known-answer tests on the corresponding SHA1
	          implementation. These tests do not encompass the full
	          range of available test vectors, however, if the tests
	          pass it is very, very likely that the code is correct
	          and was compiled properly. This code also serves as
	          example usage of the functions.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "sha256.h"
#include "sha256.c"

/*********************** FUNCTION DEFINITIONS ***********************/
void print_buf(BYTE buf[SHA256_BLOCK_SIZE]);
void print_state(WORD state[8]);

void sha256_test()
{
	BYTE text1[] = {"neon"};
	
	BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, text1, strlen(text1));
	sha256_final(&ctx, buf);
	for(int i=0; i<32; i++){
		printf("%d ", buf[i]);
	}
	printf("\n");
}

int main()
{
	sha256_test();
	return(0);
}

void print_state(WORD state[8]){
	for(int i=0; i<8; i++){
		printf("%08x", state[i]);
	}
	printf("\n");
}