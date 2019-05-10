#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include "sha256.h"
#include "sha256.c"
#include "functions.h"
#include "algos.h"


void four_letter_bruteforce(int hashes[10][32]);

int main(int argc, char *argv){
   // If this is removed there is a segfault for some reason
   unsigned char buffer[320];

   int hashes[10][32];
   save_hashes(hashes);
   //print_hashes(hashes);
   four_letter_bruteforce(hashes);
   
   return 0;
}

