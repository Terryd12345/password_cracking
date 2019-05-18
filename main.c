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

int main(int argc, char **argv){

   if( argc == 1) {
      int hashes[30][32];
      save_hashes(hashes);
      //four_letter_bruteforce(hashes);
      
      /* Get all 6 letter common passwords, only needs to be run once to generate file */
      //clean_common_passwords();

      check_six_letter_passwords(hashes);
      //print_hashes(hashes);

      combos_of_my_username(hashes);

      
   } else if( argc == 2 ){
      printf("%s\n", argv[1]);
   } else if( argc == 3 ){
      printf("%s %s\n", argv[1], argv[2]);
   } else {
      printf("Too many arguments...\n");
   }
   
   
   
   
   
   return 0;
}

