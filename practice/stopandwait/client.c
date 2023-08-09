#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8000

typedef struct packet
{
    char data[1024];
} Packet;

typedef struct frame
{
    int frame_kind;
    int sq_no;
    int ack;
    Packet packet;
} Frame;

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[1024];

    int frame_id = 0;
    Frame frame_recv;
    Frame frame_send;
    int ack_recv = 1;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    while (1)
    {
        if (ack_recv == 1)
        {
            frame_send.sq_no = frame_id;
            frame_send.frame_kind = 1;
            frame_send.ack = 0;

            printf("Enter Data : ");
            scanf("%s", buffer);
            strcpy(frame_send.packet.data, buffer);
            sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
            printf("[+]Frame Send\n");
        }
        int addr_size = sizeof(servaddr);
        int f_recv_size = recvfrom(sockfd, &frame_recv, sizeof(frame_recv), 0, (struct sockaddr *)&servaddr, &addr_size);
        if (f_recv_size > 0 && frame_recv.sq_no == 0 && frame_recv.ack == frame_id + 1)
        {
            printf("[+]Ack Recieved\n");
            ack_recv = 1;
        }
        else
        {
            printf("[-]Ack Not Recieved\n");
            ack_recv = 0;
        }
        frame_id++;
    }
    close(sockfd);
    return 0;
}