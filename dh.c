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
    int b = atoi(argv[1]);
    printf("b: %d\n", b);
    int g = 15;
    int p = 97;
    int gamodp; // will be sent by server
    int public_key = compute_key(g, b, p);

    printf("g^b(mod p): %d\n", public_key);

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent * server;

    char buffer[256];

    portno = 7800;


    /* Translate host name into peer's IP address ;
     * This is name translation service by the operating system
     */
    server = gethostbyname("172.26.37.44");

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    /* Building data structures for socket */

    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy(server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);

    /* Create TCP socket -- active open
    * Preliminary steps: Setup: creation of active open socket
    */

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

    /* Send g^b mod p value */
    

    bzero(buffer, 256);

    char b_string[4];
    sprintf(b_string, "%d\n", public_key);

    strcpy(buffer, b_string);

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
    }

    
    /* Get response 
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

    /* Send secret key */

    bzero(buffer, 256);

    char private_key[2];
    int private_key_int = compute_key(g, gamodp*b, p);
    sprintf(private_key, "%d", private_key_int);

    n = write(sockfd, private_key, strlen(private_key));

    if (n < 0)
    {
        perror("ERROR writing to socket");
    }

    /* Get response 
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

// Function to compute a^m mod n
int compute_key(int g, int m, int p)
{
	int r;
	int y = 1;

	while (m > 0)
	{
		r = m % 2;

		// fast exponention 
		if (r == 1)
			y = (y*g) % p;
		g = g*g % p;

		m = m / 2;
	}

	return y;
}