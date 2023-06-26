#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
int main()
{
    int socket_desc,client_size, client_sock,n,f;
    struct sockaddr_in server_addr,client_addr;
    char filename[100], filedata[300];
    socket_desc = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
        printf("Can't bind");
    listen(socket_desc,5);
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
    n = read(client_sock,filename,100);
    filename[n] = 0;
    printf("\nRequested file from the client is: %s",filename);
    f = open(filename,O_RDWR);
    n = read(f,filedata,300);
    printf("\nThe contents of the file is: \n\n");
    printf("%s",filedata);
    write(client_sock,filedata,n);
    close(client_sock);
    close(socket_desc);
    return 0;
}
