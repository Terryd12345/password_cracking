#include <stdio.h>

void save_hashes(int hashes[10][32]);
void print_hashes(int hashes[10][32]);
void print_word(int word[]);
void read_commonpasswords();
void four_letter_bruteforce(int hashes[10][32]);
void clean_common_passwords();
void check_six_letter_passwords(int hashes[30][32]);

/* Reads binary files and saves hash values in an array */ 
void save_hashes(int hashes[30][32]){

    /* Read in first 10 hashes */
    unsigned char buffer[320];
    FILE *fp;
    fp = fopen("pwd4sha256", "rb");
    
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fread(buffer,sizeof(buffer),1,fp);
    fclose(fp);
    
    // Loop over first 10 hashes and save them
    int j=0, e=0;
    for(int i = 0; i<320; i++){
        if( (i%32 == 0) && (i>0) ){
            j++;
            e = 0;
        }
        hashes[j][e] = buffer[i];  
        e++;
    }

    // save rest of hashes
    unsigned char buffer2[640];
    FILE *fp2;
    fp2 = fopen("pwd6sha256", "rb");
    fread(buffer2, sizeof(buffer2), 1, fp2);
    fclose(fp2);

    j=9;
    for(int i = 0; i<640; i++){
        if( i%32 == 0 ){
            j++;
            e = 0;
        }
        hashes[j][e] = buffer[i];  
        e++;
    }

}

/* Used to print hash values from array */
void print_hashes(int hashes[30][32]){
   for(int i=0; i<30; i++){
       for(int j=0; j<32; j++){
           printf("%02x", hashes[i][j]);
       }
       printf("\n");
   }
}

/** 
 * n^4 brute force search of all potential four char combinations
 * prints out matching hashes as well as the index
 * **/
void four_letter_bruteforce(int hashes[30][32]){
    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    BYTE word[4];
    int a,b,c,d;
    int found = 1;
    int words_found = 0;
    
    for(a=32; a<127; a++){
        if( words_found == 10 ) break;
        for(b=32; b<127; b++){
            if( words_found == 10 ) break;
            for(c=32; c<127; c++){
                if( words_found == 10 ) break;
                for(d=32; d<127; d++){
                    if( words_found == 10 ) break;
                    word[0] = a;
                    word[1] = b;
                    word[2] = c;
                    word[3] = d;
                    word[4] = '\0';
                    
                    sha256_init(&ctx);
                    sha256_update(&ctx, word, sizeof(word));
                    sha256_final(&ctx, buf);
                    
                    for(int j=1; j<11; j++){
                        found = 1;
                        for(int i=0; i<32; i++){
                            if( buf[i] != hashes[j][i] ){
                                found = 0;
                                break;
                            }
                        }
                        if( found == 1 ){
                            words_found++;
                            ctx.data[4] = '\0';
                            printf("%s %d\n", ctx.data, j);
                        }
                    }  
                }
            }              
        }
    }
}

/* Find all 6 letter common passwords and pass them into new file */
void clean_common_passwords(){
    FILE *fp;
    FILE *fp2;
    char str[20];
    char* filename = "common_passwords.txt";
    char* filename2 = "six_letter_common_passwords.txt";
 
    fp = fopen(filename, "r");
    fp2 = fopen(filename2, "w");

    if (fp == NULL){
        printf("Could not open file %s",filename);
        exit(0);
    }
    if (fp2 == NULL){
        printf("Could not open file %s",filename);
        exit(0);
    }

    while (fgets(str, 20, fp) != NULL)
        if(strlen(str) == 6){
           fprintf (fp2, "%s", str);
        }
        
    fclose(fp);
    fclose(fp2);
}

void check_six_letter_passwords(int hashes[30][32]){

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
      memcpy(word, str, sizeof(word));
      
      sha256_init(&ctx);
      sha256_update(&ctx, word, sizeof(word));
      sha256_final(&ctx, buf);
      
      // print each password as a hash
      for(int i=0; i<32; i++){
         printf("%02x", buf[i]);
      }
      printf("\n");
      
   }
   

   fclose(fp);

}