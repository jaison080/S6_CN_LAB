#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#define PORT 8001

int main()
{
    int sockfd,n;
    struct sockaddr_in servaddr;
    char filename[1024],newfilename[1024],content[1024];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("Enter File Name : ");
    scanf("%s",filename);
    send(sockfd,&filename,sizeof(filename),0);
    printf("Enter New File Name : ");
    scanf("%s",newfilename);
    send(sockfd,&newfilename,sizeof(newfilename),0);
    n=recv(sockfd,&content,1024,0);
    content[n]='\0';
    printf("Content : %s\n",content);
    close(sockfd);
    return 0;
}