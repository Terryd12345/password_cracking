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

int compute_key(int g, int m, int p);


int main(int argc, char ** argv)
{
    //char *openssl_result = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    
    //int b = 1; // e3
    //int g = 15;
    //int p = 97;

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

    /* ----------------------- end setup -------------------------- */

    /* Send username
    */

    bzero(buffer, 256);

    strcpy(buffer, "tdenning\n");

    printf("Sending name: tdenning\n");

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(0);
    }

    /* Send g^b(mod p) value */
    

    bzero(buffer, 256);

    strcpy(buffer, "15\n");

    printf("Writing g^b(mod p): %s\n", buffer);

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
    }

    
    /* Get response, should receive g^a(mod p)
    */

    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(0);
    }

    gamodp = atoi(buffer);

    printf("g^a(mod p): %d\n", gamodp);

    /* Send secret key 
    */

    bzero(buffer, 256);

    n = write(sockfd, "10", strlen("10")); // write g^ab(mod p)

    if (n < 0)
    {
        perror("ERROR writing to socket");
    }

    /* Get response ( hopefully get passwords )
    */

    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(0);
    }

    printf("%s\n", buffer);

    return 0;
}
