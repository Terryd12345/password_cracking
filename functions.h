#include <stdio.h>

void save_hashes(int hashes[10][32]);
void print_hashes(int hashes[10][32]);
void print_word(int word[]);
void read_commonpasswords();
void four_letter_bruteforce(int hashes[10][32]);

void save_hashes(int hashes[10][32]){
    unsigned char buffer[320];
    FILE *fp;
   fp = fopen("pwd4sha256", "rb"); // read mode
 
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
       if( i%32 == 0 ){
           j++;
           e = 0;
       }
       hashes[j][e] = buffer[i];  
       e++;
   }
}

void print_hashes(int hashes[10][32]){
    // Loop over our current saved hashes 
   for(int i=1; i<11; i++){
       for(int j=0; j<32; j++){
           printf("%02x", hashes[i][j]);
       }
       printf("\n");
   }
}

void read_commonpasswords(){
    FILE *fp;
    fp = fopen("common_passwords.txt", "r");
    char ch;
    char word[100];
    int i = 0;
    
    while( (ch = getc(fp)) != EOF )
    {
        if( ch == '\n' ){
            printf("%s\n", word);
            memset(word, '\0', 100);
            i = 0;
        } else {
            word[i] = ch;
            i++;
        }
    }
    fclose(fp);
}

/** 
 * n^4 brute force search of all potential four char combinations
 * prints out matching hashes as well as the index
 * **/
void four_letter_bruteforce(int hashes[10][32]){
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