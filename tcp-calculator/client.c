#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 80
#define PORT 8082
#define SA struct sockaddr
void func(int sockfd)
{
    char buffer[MAX];
    int n;
    int num1, num2, ans=0, choice;
S:
    bzero(buffer, MAX);
    n = recv(sockfd, buffer, 255,0);
    printf("Server - %s\n", buffer);
    scanf("%d", &num1);
    send(sockfd, &num1, sizeof(int),0);
    bzero(buffer, MAX);
    n = recv(sockfd, buffer, 255,0);
    printf("Server - %s\n", buffer);
    scanf("%d", &num2);
    send(sockfd, &num2, sizeof(int),0);
    bzero(buffer, MAX);
    n = recv(sockfd, buffer, 255,0);
    printf("Server - %s\n", buffer);
    scanf("%d", &choice);
    send(sockfd, &choice, sizeof(int),0);
    if (choice == 5)
    {
        printf("You have selected to Exit...\n");
        exit(0);
    }
    recv(sockfd, &ans, sizeof(int), 0);
    printf("Server - The Answer is %d\n", ans);
    if (choice != 5)
        goto S;
}
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket Creation Failed...\n");
        exit(0);
    }
    else
        printf("Socket Successfully Created..\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection with the Server Failed...\n");
        exit(0);
    }
    else
        printf("Connected to the Server..\n");
    func(sockfd);
    close(sockfd);
}