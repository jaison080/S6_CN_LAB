#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 8004

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    char word[1024], buffer[1024];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Enter the word : ");
    scanf("%s", word);
    send(sockfd, word, sizeof(word), 0);
    recv(sockfd, &buffer, 1024, 0);
    printf("Result : %s", buffer);
    close(sockfd);
    return 0;
}