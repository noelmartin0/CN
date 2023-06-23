#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
    printf("Client\n");
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[200], client_message[200];
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    socket_desc = socket(AF_INET,SOCK_STREAM,0);
    if(socket_desc<0)
    {
        printf("\nError while creating the socket");
        return -1;
    }
    printf("\nSocket Created successfully");
    server_addr.sin_family =AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(socket_desc,(struct socketaddr*)&server_addr, sizeof(server_addr)) <0) 
    {
        printf("\nFailed to connect");
        return -1;
    }
    printf("\nConnected to the server successfully");
    printf("\nEnter message: ");
    gets(client_message);
    if(send(socket_desc, client_message, strlen(client_message),0)<0)
    {
        printf("\nUnable to send the message");
        return -1;
    }
    if(recv(socket_desc, server_message, sizeof(server_message),0)<0)
    {
        printf("\nError while receiving the message");
        return -1;
    }
    printf("\nServer's response: %s",server_message);
    close(socket_desc);
    return 0;
}