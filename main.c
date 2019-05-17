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
   four_letter_bruteforce(hashes);
   
   return 0;
}

