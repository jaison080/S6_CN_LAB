#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include<string.h>
#include<ctype.h>
#define PORT 8001

int main()
{
    int sockfd, connfd, len, n1, n2;
    char filename[1024], newfilename[1024], content[1024], newcontent[1024];
    FILE *fp1, *fp2;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);
    len = sizeof(cli);
    connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    n1 = recv(connfd, &filename, 1024, 0);
    filename[n1] = '\0';
    printf("Old File : %s\n",filename);
    n2 = recv(connfd, &newfilename, 1024, 0);
    newfilename[n2] = '\0';
    printf("New File : %s\n",newfilename);
    fp1 = fopen(filename, "r");
    fgets(content, sizeof(content), fp1);
    for(int i=0;i<strlen(content);i++)
    {
        newcontent[i]=toupper(content[i]);
    }
    newcontent[strlen(content)]='\0';
    fclose(fp1);
    fp2 = fopen(newfilename, "w");
    fputs(newcontent, fp2);
    fclose(fp2);
    send(connfd, &newcontent, sizeof(newcontent), 0);
    close(sockfd);
    close(connfd);
    return 0;
}