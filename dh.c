/* A simple client program for server.c

   To compile: gcc client.c -o client

   To run: start the server, then the client */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <math.h> 
#include <sys/types.h>  
#include <sys/wait.h> 

int compute_key(int g, int m, int p);

int main(int argc, char ** argv)
{
    
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent * server;

    int gamodp;

    char buffer[256];


    /* ----------------------- setup server connection -------------------------- */

    server = gethostbyname("172.26.37.44");
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(7800);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(0);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR connecting");
        exit(0);
    }

    /* ----------------------- end server connection setup -------------------------- */



    /* ----------------------- Send username -------------------------- */

    bzero(buffer, 256);

    strcpy(buffer, "tdenning\n");

    printf("Sending name: tdenning\n");

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(0);
    }

    /* ----------------------- end send username -------------------------- */

    /* ----------------------- send g^b(mod p) -------------------------- */

    bzero(buffer, 256);

    sprintf(buffer, "%s\n", argv[1]);

    printf("g^b(mod p): %s\n", buffer);

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
    }

    /* ----------------------- receive g^a(mod p) -------------------------- */

    /* Receive g^a(mod p) */

    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(0);
    }

    gamodp = atoi(buffer);

    printf("g^a(mod p): %d\n", gamodp);


    /* ----------------------- Generate g^b(mod p) -------------------------- */

    pid_t pid;

    if( argc != 2 ){
        printf("Forgot to include B as argument.\n");
        exit(0);
    }

    pid = fork();

    if( pid < 0 ){
        printf("failed to create child\n"); 
        exit(0); 
    } else if( pid == 0 ){ // child process
        /* Calculate g^b(mod p) */
        char *gbmodp_input;
        sprintf(gbmodp_input, "15 %s 97 | p", argv[1]);
        execl("/usr/bin/dc", gbmodp_input, NULL);

    } else { // parent process
        wait(NULL);

        /* Calculate g^ab(mod p) and send */

        bzero(buffer, 256);

        n = write(sockfd, "10", strlen("10")); // write g^ab(mod p)

        if (n < 0)
        {
            perror("ERROR writing to socket");
        }

        /* Receive response from server */

        bzero(buffer, 256);

        n = read(sockfd, buffer, 255);

        if (n < 0)
        {
            perror("ERROR reading from socket");
            exit(0);
        }

        printf("%s\n", buffer);


        printf("Done\n");
    }

    /* ----------------------- end processes -------------------------- */
    
    

    return 0;
}