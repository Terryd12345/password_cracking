#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv){
   unsigned char buffer[320];

   char file_name[25] = "pwd4sha256";
   FILE *fp;
 
   fp = fopen(file_name, "rb"); // read mode
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

   fread(buffer,sizeof(buffer),1,fp);
    
   // Convert binary values into hexidecimal strings 
   char hex_value[3];
   char full_hex[32];
   
   // Loop through input and create hexidecimal strings 
   for(int i = 0; i<320; i++){
       if( i%32 == 0 ){
           printf("%s\n", full_hex);
           memset(full_hex, '\0', 32);
       }
       sprintf(hex_value, "%02x", buffer[i]);
       strncat(full_hex, hex_value, 3);
   }
   printf("%s", full_hex);
    
   fclose(fp);
   printf("\n\n");
   
   return 0;
}
