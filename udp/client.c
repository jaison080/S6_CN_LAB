#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

void main()
{
    int client;
    struct sockaddr_in servAddr;
    char servMsg[2000], cliMsg[2000];
    socklen_t server_struct_length = sizeof(servAddr);

    client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client < 0)
    {
        printf("Error while creating socket\n");
        exit(1);
    }
    printf("Socket created successfully...\n");

    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(7000);

    printf("Enter message to server : ");
    fgets(cliMsg, sizeof(cliMsg), stdin);

    if (sendto(client, cliMsg, strlen(cliMsg), 0, (struct sockaddr *)&servAddr, server_struct_length) < 0)
    {
        printf("Unable to send message...\n");
        exit(1);
    }

    if (recvfrom(client, servMsg, sizeof(servMsg), 0, (struct sockaddr *)&servAddr, &server_struct_length) < 0)
    {
        printf("Error while receiving message...\n");
        exit(1);
    }

    printf("Server response: %s\n", servMsg);

    close(client);
}