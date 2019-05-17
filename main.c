#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include "sha256.h"
#include "sha256.c"
#include "functions.h"


int main(int argc, char **argv){
   int hashes[30][32];
   save_hashes(hashes);
   //four_letter_bruteforce(hashes);
   clean_common_passwords();


   /* ----------------- Find 6 letter passwords ------------------- */

   BYTE buf[SHA256_BLOCK_SIZE];
   SHA256_CTX ctx;
   BYTE word[6];
   char str[6];

   FILE *fp;
   char* filename = "six_letter_common_passwords.txt";
   fp = fopen(filename, "r");

   if (fp == NULL){
        printf("Could not open file %s",filename);
        exit(0);
    }

   int found = 1;

   while (fgets(str, 6, fp) != NULL){
      printf("%s", str);   
      
      sha256_init(&ctx);
      sha256_update(&ctx, word, sizeof(word));
      sha256_final(&ctx, buf);

      for(int j=10; j<30; j++){
         found = 1;
         for(int i=0; i<32; i++){
               if( buf[i] != hashes[j][i] ){
                  found = 0;
                  break;
               }
         }
         if( found == 1 ){
               ctx.data[6] = '\0';
               printf("%s %d\n", ctx.data, j);
         }
      }
   }


   
   
   return 0;
}

