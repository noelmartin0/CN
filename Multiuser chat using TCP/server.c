#include<stdio.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

pthread_mutex_t mutex;
int clients[20];
int n = 0;

void sendToAll(char *msg, int curr)
{
    pthread_mutex_lock(&mutex);
    for(int i = 0; i<n; i++)
    {
        if(clients[i] != curr)
        {
            if(send(clients[i],msg,strlen(msg),0)<0)
            {
                printf("\nFailed to send");
                continue;
            }
        }
    }
    pthread_mutex_unlock(&mutex);
}

void *receive_msg(void *client_sock)
{
    int sock = *((int*)client_sock);
    char msg[500];
    int len;
    while(len = recv(sock,msg,500,0)>0)
    {
        msg[len] = " ";
        sendToAll(msg,sock);
    }
}

int main()
{
    int socket_desc, client_sock=0;
    struct sockaddr_in server_addr;
    pthread_t recvt;
    socket_desc = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(socket_desc,(struct sockaddr*)&server_addr, sizeof(server_addr))<0)
        printf("\nFailed to bind");
    printf("\nBinded sucessfully");
    if(listen(socket_desc,20)<0)
        printf("\nError while listening");
    while(1)
    {
        if((client_sock = accept(socket_desc, (struct sockaddr*)NULL,NULL))<0)
            printf("\nFailed to accept");
        pthread_mutex_lock(&mutex);
        clients[n] = client_sock;
        n++;
        pthread_create(&recvt,NULL,(void *)receive_msg,&client_sock);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}