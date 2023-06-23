#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
    int socket_desc;
    struct sockaddr_in server_addr, client_addr;
    char server_message[200], client_message[200];
    memset(server_message,'\0', sizeof(server_message));
    memset(client_message,'\0', sizeof(client_message));
    socket_desc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    int client_length = sizeof(client_addr);
    if(socket_desc<0)
    {
        printf("\nError while creating socket");
        return -1;
    }
    printf("\nSocket created successfully");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(socket_desc,(struct sockaddr*)&server_addr, sizeof(server_addr))<0)
    {
        printf("\nFailed to bind");
        return -1;
    }
    printf("\nBinded successfully");
    printf("\nListening for incomimg connection...");
    if(recvfrom(socket_desc, client_message, sizeof(client_message),0, (struct sockaddr*)&client_addr, &client_length)<0)
    {
        printf("\nCouldn't receive");
        return -1;
    }
    printf("\nReceived message from IP %s and port %i",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    printf("\nMessage: %s",client_message);
    printf("\nEnter server message: ");
    gets(server_message);
    if(sendto(socket_desc, server_message, strlen(server_message),0, (struct sockaddr*)&client_addr, client_length)<0)
    {
        printf("\nFailed to send");
        return -1;
    }
    close(socket_desc);
    return 0;
}