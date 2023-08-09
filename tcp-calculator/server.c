#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8082
#define SA struct sockaddr
void func(int connfd)
{
    int num1,num2,choice,ans=0;
    S: send(connfd,"Enter Number 1 : ",strlen("Enter Number 1"),0);
    recv(connfd,&num1,sizeof(int),0);
    printf("Client Number 1 is : %d\n",num1);
    send(connfd,"Enter Number 2 : ",strlen("Enter Number 2"),0);
    recv(connfd,&num2,sizeof(int),0);
    printf("Client Number 2 is : %d\n",num2);
    send(connfd,"1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n",strlen("1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n"),0);
    send(connfd,"Enter Choice : ",strlen("Enter Choice"),0);
    recv(connfd,&choice,sizeof(int),0);
    printf("Client Choice is : %d\n",choice);
    switch(choice)
    {
        case 1:
            ans=num1+num2;
            break;
        case 2:
            ans=num1-num2;
            break;
        case 3:
            ans=num1*num2;
            break;
        case 4:
            ans=num1/num2;
            break;
        case 5:
            exit(0);
    }
    send(connfd,&ans,sizeof(int),0);
    if(choice!=5)
        goto S;
}
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("Server Sccept Failed...\n");
        exit(0);
    }
    else
        printf("Server Accept the Client...\n");
    func(connfd);
    close(sockfd);
}