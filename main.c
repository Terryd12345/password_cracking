#include <stdio.h>
#include <stdlib.h>

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
 
 
   for(int i = 0; i<320; i++){
       if( i%32 == 0 ){
           printf("\n\n");
       }
       if( i%2 == 1 ){
           printf("%x ", buffer[i]);
       } else {
           printf("%x", buffer[i]);
       }
       
   }
    
   fclose(fp);
   printf("\n\n");
   
   return 0;
}