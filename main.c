#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include "sha256.h"
#include "sha256.c"
#include "functions.h"

// ASCII values -> 32 to 126
void four_letter_bruteforce();

int main(int argc, char *argv){
   // If this is removed there is a segfault for some reason
   unsigned char buffer[320];

   int hashes[10][32];
   save_hashes(hashes);
   //print_hashes(hashes);
   four_letter_bruteforce();
   
   return 0;
}

void four_letter_bruteforce(){
    //BYTE buf[SHA256_BLOCK_SIZE];
    //SHA256_CTX ctx;
    char word[4];
    int a,b,c,d;
    
    for(a=32; a<127; a++){
        for(b=32; b<127; b++){
            for(c=32; c<127; c++){
                for(d=32; d<127; d++){
                    word[0] = a;
                    word[1] = b;
                    word[2] = c;
                    word[3] = d;
                    printf("%s\n", word);
                    
                    //sha256_init(&ctx);
                    //sha256_update(&ctx, word, strlen(word));
                    //sha256_final(&ctx, buf);
                    //printf("%s\n", ctx.data);
                }
            }              
        }
    }
}