#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/**
int main(int argc, char *argv){
   unsigned char buffer[320];
    char curr[32] = "";

   char file_name[25] = "pwd4sha256";
   FILE *fp;
 
   fp = fopen(file_name, "rb"); // read mode
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

   fread(buffer,sizeof(buffer),1,fp);
 
 
   for(int i = 0; i<320; i++){
        if( i%32 == 0 ){
            printf("\n\n");
        }
        
        printf("%02x ", buffer[i]);
       
       
   }
    
   fclose(fp);
   printf("\n\n");
   
   return 0;
}**/
#include <openssl/sha.h>
 
int main () {
	const char *s = "Rosetta code";
	unsigned char *d = SHA256(s, strlen(s), 0);
 
	int i;
	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
		printf("%02x", d[i]);
	putchar('\n');
 
	return 0;
}
