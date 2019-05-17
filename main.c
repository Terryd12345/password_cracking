#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include "sha256.h"
#include "sha256.c"
#include "functions.h"

void passwords();

int main(int argc, char **argv){
   int hashes[30][32];
   save_hashes(hashes);
   //four_letter_bruteforce(hashes);
   
   /* Get all 6 letter common passwords, only needs to be run once to generate file */
   //clean_common_passwords();

   passwords();
   //print_hashes(hashes);

   
   
   return 0;
}


void passwords(){

   BYTE buf[SHA256_BLOCK_SIZE];
   SHA256_CTX ctx;
   BYTE word[6];

   FILE *fp;
   char str[6];
   char* filename = "six_letter_common_passwords.txt";

   fp = fopen(filename, "r");
   if (fp == NULL){
      printf("Could not open file %s",filename);
      exit(0);
   }

   while (fgets(str, 6, fp) != NULL){
      memset(word, '\0', 6);
      int dec_value;
      for( int i=0; i<6; i++){
         dec_value = str[i];
         if( dec_value < 0 ){
            word[i] = dec_value + 256;
         } else {
            word[i] = dec_value;
         }
      }
      word[6] = '\0';
      

      sha256_init(&ctx);
      sha256_update(&ctx, word, sizeof(word));
      sha256_final(&ctx, buf);
      printf("%s", word);
   }

   fclose(fp);

}
