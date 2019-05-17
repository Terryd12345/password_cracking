#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include "sha256.h"
#include "sha256.c"
#include "functions.h"

void check_six_letter_passwords(int hashes[30][32]);

int main(int argc, char **argv){
   int hashes[30][32];
   save_hashes(hashes);
   //four_letter_bruteforce(hashes);
   
   /* Get all 6 letter common passwords, only needs to be run once to generate file */
   //clean_common_passwords();

   check_six_letter_passwords(hashes);

   
   
   return 0;
}

