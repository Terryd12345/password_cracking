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
   char username[6] = "tdenni";

   for(int a=0; a<6; a++){
      username[a] = toupper(username[a]);
      for(int b=0; b<6; b++){
         username[b] = toupper(username[b]);
         for(int c=0; c<6; c++){
            username[c] = toupper(username[c]);
            for(int d=0; d<6; d++){
               username[d] = toupper(username[d]);
               for(int e=0; e<6; e++){
                  username[e] = toupper(username[e]);
                  for(int f=0; f<6; f++){
                     username[f] = toupper(username[f]);
                     printf("%s\n", username);
                  }
               }
            }
         }
      }
   }
}