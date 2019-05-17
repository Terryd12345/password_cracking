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


int compute(int g, int x, int p);

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

    /* ----------------------- Generate g^b(mod p) -------------------------- */

    bzero(buffer, 256);

    if( argc != 2 ){
        printf("Forgot to include B as argument.\n");
        exit(0);
    }

    int gbmodp = compute(15, atoi(argv[1]), 97);
    sprintf(buffer, "%d\n", gbmodp);

    printf("Sending gbmodp: %d\n", gbmodp);
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
    }
    

    /* ----------------------- Receive g^a(mod p) -------------------------- */

    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(0);
    }

    gamodp = atoi(buffer);

    printf("Receieved g^a(mod p): %d\n", gamodp);

    /* ----------------------- Generate g^a*b(mod p) -------------------------- */


    if( argc != 2 ){
        printf("Forgot to include B as argument.\n");
        exit(0);
    }

    

    bzero(buffer, 256);

    int shared_key = compute(gamodp, atoi(argv[1]), 97);

    sprintf(buffer, "%d\n", shared_key);

    printf("Sending gabmodp: %d\n", gbmodp);
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
    }

    /* ----------------------- Receive confirmation from server -------------------------- */


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
// https://www.techiedelight.com/c-program-demonstrate-diffie-hellman-algorithm/
int compute(int g, int x, int p)
{
	int r;
	int y = 1;

	while (x > 0)
	{
		r = x % 2;

		// fast exponention 
		if (r == 1)
			y = (y*g) % p;
		g = g*g % p;

		x = x / 2;
	}

	return y;
}