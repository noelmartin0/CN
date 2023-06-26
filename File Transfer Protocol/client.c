#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main()
{
    int socket_desc, length,rd;
    char filename[20],filedata[3000];
    struct sockaddr_in server_addr;
    socket_desc = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("\nCannot Connect");
        return -1;
    }
    printf("\nEnter the filename: ");
    scanf("%s",filename);
    length = strlen(filename);
    write(socket_desc,filename,length);
    rd = read(socket_desc,filedata,3000);
    printf("\nThe content of the file is: \n\n");
    printf("%s",filedata);
    close(socket_desc);
    return 0;
}