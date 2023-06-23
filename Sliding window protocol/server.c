#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    char server_message[200], client_message[200];
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    socket_desc = socket(AF_INET,SOCK_STREAM,0);
    if(socket_desc<0)
    {
        printf("\nError while creating socket");
        return -1;
    }
    printf("\nSocket created successfully");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("\nUnable to bind");
        return -1;
    }
    printf("\nBinded successfully");
    if(listen(socket_desc,1)<0)
    {
        printf("\nUnable to listen");
        return -1;
    }
    printf("\nListening for incoming connections...\n");
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc,(struct sockaddr*)&client_addr, &client_size);
    if(client_sock <0)
    {
        printf("\nCan't accept");
        return -1;
    }
    printf("Client connected at IP: %s and port: %i",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    while(1)
    {
        if(recv(client_sock, client_message, sizeof(client_message),0)<0)
        {
            printf("\nCouldn't receive");
            return -1;
        }
        printf("\nMessage from client: %s",client_message);
        memset(server_message,'\0', sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));
        printf("\nServer Acknowledges or not:? Ack- Y or y, NACK- N or n: ");
        z:
        memset(server_message,'\0', sizeof(server_message));
        scanf("%s",server_message);
        if(send(client_sock,server_message,strlen(server_message),0)<0)
        {
            printf("\nCan't send");
            return -1;
        }
        if(strcmp(server_message,"N")==0 || strcmp(server_message,"n")==0)
        {
            printf("\nAcknowledgement not received by client");
            goto z;
        }
    }
    close(client_sock);
    close(socket_desc);
    return 0;
}