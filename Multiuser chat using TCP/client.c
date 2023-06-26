#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>

char msg[500];

void *receive_msg(void *my_sock)
{
    int sock = *((int *)my_sock);
    int len;
    while(len = recv(sock,msg,500,0)>0)
    {
        msg[len] = " ";
        fputs(msg,stdout);
    }
}

int main(int argc, char *argv[])
{
    pthread_t recvt;
    int socket_desc,len;
    struct sockaddr_in server_addr;
    char send_msg[500],client_name[100];
    strcpy(client_name,argv[1]);
    socket_desc = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
        printf("\nFailed to connect");
    pthread_create(&recvt,NULL,(void *)receive_msg,&socket_desc);
    while(fgets(msg,500,stdin)>0)
    {
        strcpy(send_msg,client_name);
        strcat(send_msg,":");
        strcat(send_msg,msg);
        len = write(socket_desc,send_msg,strlen(send_msg));
        if (len<0)
            printf("Message not sent");
    }
    pthread_join(recvt,NULL);
    close(socket_desc);
    return 0;
}