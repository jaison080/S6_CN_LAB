#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

void main()
{
    int server;
    struct sockaddr_in servAddr,client_addr;
    char servMsg[2000],cliMsg[2000];
    int client_struct_length=sizeof(client_addr);
    server=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(server<0)
    {
        printf("Error while creating socket...\n");
        exit(1);
    }
    printf("Socket created successfully..\n");
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(7000);
    if((bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr))<0))
    {
        printf("couldn't bind to port...\n");
        exit(1);
    }
    printf("Binding Done...\n");
    printf("Listening...\n");
    if((recvfrom(server,cliMsg,sizeof(cliMsg),0,(struct sockaddr*)&client_addr,&client_struct_length)<0))
    {
        printf("Couldn't recieve...\n");
        exit(1);
    }
    printf("Msg from client: %s",cliMsg);
    strcpy(servMsg,cliMsg);
    if(sendto(server,servMsg,strlen(servMsg),0,(struct sockaddr*)&client_addr,client_struct_length)<0)
    {
        printf("Can't send...\n");
        exit(1);
    }
    close(server);
}