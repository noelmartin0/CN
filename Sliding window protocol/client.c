#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
    int socket_desc,frames,timer;
    struct sockaddr_in server_addr,client_addr;
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
    if(connect(socket_desc,(struct sockaddr*)&server_addr, sizeof(server_addr))<0)
    {
        printf("\nFailed to connect");
        return -1;
    }
    printf("\nConnect with server successfully");
    printf("\nEnter the number of frames: ");
    scanf("%d",&frames);
    while(frames>0)
    {
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));
        printf("\nEnter frame message: ");
        scanf("%s",client_message);
        x:
        timer = 10;
        if(send(socket_desc,client_message,strlen(client_message),0)<0)
        {
            printf("\nCan't send");
            return -1;
        }
        y:
        if(timer>0)
        {
            if(recv(socket_desc,server_message,sizeof(server_message),0)<0)
            {
                printf("\nFailed to receive the message");
                timer--;
                goto y;
            }
            if(strcmp(server_message,"Y")==0||strcmp(server_message,"y")==0)
            {
                printf("\nServer acknowledged!");
                timer = 0;
                frames--;
            }
            if(strcmp(server_message,"N")==0||strcmp(server_message,"n")==0)
            {
                printf("\nWaiting........");
                timer--;
                goto y;
            }
        }
        else
        {
            printf("\nServer do not acknowledfed\nResending....");
            goto x;
        }
    }
    close(socket_desc);
    return 0;
}