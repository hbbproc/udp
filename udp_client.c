#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main()
{
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in remote;
    remote.sin_family = AF_INET;
    remote.sin_port = htons(8080);
    //remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t len = sizeof(remote);
    //socklen_t len = 0;
    
    while(1)
    {
        char buf[1024];
        memset(buf,'\0',sizeof(buf));
        ssize_t _size =  read(0,buf,sizeof(buf)-1);
        buf[_size] = '\0';
        printf("%s\n",buf);
        //fflush(stdout);
        _size = sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&remote,len);
        // printf("%d\n",_size);
        _size = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
        // printf("%d\n",_size);
        //_size = send(sock,buf,strlen(buf),0);
        //_size = recv(sock,buf,sizeof(buf)-1,0);
        if(_size > 0)
        {
            printf("server echo:%s\n");
        }
    }
    close(sock);
    return 0;
}
