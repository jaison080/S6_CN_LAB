#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *fp;
    int port, sd, a, bd, clilen, n, connfd;
    char rcv[100], fileread[1000];
    struct sockaddr_in servaddr, cli;
    printf("Enter the port address : ");
    scanf("%d", &port);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
        printf("Can't Create...\n");
    else
        printf("Socket Created...\n");
            servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    servaddr.sin_family = AF_INET;
    a = sizeof(servaddr);
    bd = bind(sd, (struct sockaddr *)&servaddr, a);
    if (bd < 0)
        printf("Can't bind...\n");
    else
        printf("Binded...\n");
    listen(sd, 5);
    clilen = sizeof(cli);
    connfd = accept(sd, (struct sockaddr *)&cli, &clilen);
    if (connfd < 0)
        printf("Can't accept...\n");
    else
        printf("Accepted...\n");
    n = recv(connfd, rcv, 100, 0);
    rcv[n] = '\0';
    fp = fopen(rcv, "r");
    if (fp == NULL)
    {
        send(connfd, "error", 5, 0);
        close(connfd);
    }
    else
    {
        while (fgets(fileread, sizeof(fileread), fp))
        {
            if (send(connfd, fileread, sizeof(fileread), 0) < 0)
                printf("Can't send file contents...\n");
            sleep(1);
        }
        if(!fgets(fileread,sizeof(fileread),fp))
        {
            send(connfd,"completed",999999999,0);
        }
        return 0;
    }
}