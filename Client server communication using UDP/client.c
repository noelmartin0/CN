#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main()
{
    int socket_desc;
    char client_message[200], server_message[200];
    struct sockaddr_in server_addr, client_addr;
    memset(client_message, '\0', sizeof(client_message));
    memset(server_message, '\0', sizeof(server_message));
    socket_desc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    int server_length = sizeof(server_addr);
    if(socket_desc < 0)
    {
        printf("\nError while creating a socket");
        return -1;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("\nEnter the client message: ");
    gets(client_message);
    if(sendto(socket_desc,client_message,strlen(client_message),0,(struct sockaddr*)&server_addr, server_length)<0)
    {
        printf("\nFailed to send the message");
        return -1;
    }
    if(recvfrom(socket_desc,server_message,sizeof(server_message),0,(struct sockaddr*)&server_addr, &server_length)<0)
    {
        printf("\nFailed to receive the message");
        return -1;
    }
    printf("\nServer's response: %s",server_message);
    close(socket_desc);
    return 0;
}