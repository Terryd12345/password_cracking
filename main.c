#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <memory.h>
#include "sha256.h"
#include "sha256.c"
#include "functions.h"

void six_letter_bruteforce(int hashes[30][32]);
void combos_of_my_username(int hashes[30][32]);

int main(int argc, char **argv){
   int hashes[30][32];
   save_hashes(hashes);
   //four_letter_bruteforce(hashes);
   
   /* Get all 6 letter common passwords, only needs to be run once to generate file */
   //clean_common_passwords();

   //check_six_letter_passwords(hashes);
   //print_hashes(hashes);

   combos_of_my_username(hashes);
   
   return 0;
}

void combos_of_my_username(int hashes[30][32]){

   BYTE buf[SHA256_BLOCK_SIZE];
   SHA256_CTX ctx;

   unsigned char username[6] = "tdenni";
   unsigned char jumbled[6];
   int found;

   for( int i=0; i<6; i++ ){

      jumbled[i] = toupper(username[i]);

      for( int j=0; j<6; j++ ){
         if( j != i ){
            jumbled[j] = username[j];
         }
      }

      jumbled[6] = '\0';
      printf("%s\n", jumbled);

      sha256_init(&ctx);
      sha256_update(&ctx, jumbled, sizeof(jumbled));
      sha256_final(&ctx, buf);

      /* Check hashes */
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

}