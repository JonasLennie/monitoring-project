#include "./defaultIncludes.h"
#include "./handler.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void newConnection(int newsockfd, int clilen, struct sockaddr_in cli_addr) {
    char buffer[256];
    int n;

    if (newsockfd < 0) {
        error("ERROR on accept");
    }

     printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port)); 

     send(newsockfd, "Welcome to the echobox\n", 23, 0);

     bzero(buffer,256);

     n = read(newsockfd,buffer,255);

     if (n < 0) error("ERROR reading from socket");

     printf("Here is the message: %s\n",buffer);

    send(newsockfd, handleConnection(buffer), 255, 0);

     close(newsockfd);
}

int initConnection(int portno) {
    struct sockaddr_in serv_addr;
    int sockfd;
     
     sockfd =  socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));


     sockfd =  socket(AF_INET, SOCK_STREAM, 0);

     serv_addr.sin_family = AF_INET;  

     serv_addr.sin_addr.s_addr = INADDR_ANY;  

     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    return sockfd;
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in cli_addr;

    sockfd = initConnection(PORT_NO);

    while (1) {

        listen(sockfd,5);

        clilen = sizeof(cli_addr);

        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

        newConnection(newsockfd, clilen, cli_addr);

    }
    
    close(sockfd);
    return 0; 
} 
