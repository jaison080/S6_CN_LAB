#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
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
    int sockfd, addr_size;
    struct sockaddr_in servaddr, cli;
    char buffer[1024];

    int frame_id = 0;
    Frame frame_recv, frame_send;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    addr_size = sizeof(cli);
    while (1)
    {
        int f_recv_size = recvfrom(sockfd, &frame_recv, sizeof(Frame), 0, (struct sockaddr *)&cli, &addr_size);
        if (f_recv_size > 0 && frame_recv.frame_kind == 1 && frame_recv.sq_no == frame_id)
        {
            printf("[+]Frame Recieved : %s\n", frame_recv.packet.data);

            frame_send.sq_no = 0;
            frame_send.frame_kind = 0;
            frame_send.ack = frame_recv.sq_no + 1;
            sendto(sockfd, &frame_send, sizeof(frame_send), 0, (struct sockaddr *)&cli, addr_size);
            printf("[+]Ack Send\n");
        }
        else
        {
            printf("[+]Frame Not Recieved\n");
        }
        frame_id++;
    }
    close(sockfd);
    return 0;
}