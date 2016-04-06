#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#define _PORT_ 8080

int main()
{
    int sock = socket(AF_INET/*ipv4*/,SOCK_DGRAM,0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(_PORT_);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
   
     //local.sin_addr.s_addr = inet_addr(128.0.0.1);
     // local.sin_addr.s_addr = inet_aton("192.168.19.130",&local.sin_addr);
     //local.sin_addr.s_addr = inet_aton("127.0.0.1",&local.sin_addr);

    if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
    {
        perror("bind");
        exit(1);
    }
    struct sockaddr_in client;
    socklen_t len = 0;
    //socklen_t len = sizeof(client);
    while(1)
    {
        char buf[1024];
        memset(buf,'\0',sizeof(buf));
        ssize_t _size = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
        //ssize_t _size = recv(sock,buf,sizeof(buf)-1,0);
    if(_size < 0)
    {
        perror("revefrom");
        exit(1);
    }else if(_size == 0){
        printf("client is release!\n");
        continue;
    } else{
        buf[_size] = '\0';
        printf("client:%s\n");
        //fflush(stdout);
        sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&client,len);
        //send(sock,buf,strlen(buf),0);
    }
 }
    close(sock);
    return 0;
}
