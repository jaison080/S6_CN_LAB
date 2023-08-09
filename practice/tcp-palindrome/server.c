#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#define PORT 8004

int main()
{
    int sockfd, connfd, addr_size,n;
    char buffer[1024], revbuffer[1024];
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);
    addr_size = sizeof(cli);
    connfd = accept(sockfd, (struct sockaddr *)&cli, &addr_size);
    n=recv(connfd, &buffer, 1024, 0);
    buffer[n]='\0';
    printf("Word : %s\n",buffer);
    for (int i = 0, j = strlen(buffer) - 1; i < strlen(buffer) && j >= 0; i++, j--)
    {
        revbuffer[j] = buffer[i];
    }
    revbuffer[strlen(buffer)]='\0';
    printf("Reversed Word : %s\n",revbuffer);
    if (strcmp(buffer, revbuffer) == 0)
    {
        send(connfd,"It is Palindrome\n", sizeof("It is Palindrome"), 0);
    }
    else
    {
        send(connfd,"Not a Palindrome\n", sizeof("Not a Palindrome"), 0);
    }
    close(sockfd);
    close(connfd);
}