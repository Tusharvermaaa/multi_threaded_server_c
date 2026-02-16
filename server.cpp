#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<sys/time.h>

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<arpa/inet.h>
#include<signal.h>
#include<errno.h>
#include<fcntl.h>

#define PORT 8080
#define SA struct sockaddr 
#define MAXLINE 1024

using namespace std;

void* handler(void *arg )
{
    int clientfd= *(int *)arg;
    char req[MAXLINE] , res[MAXLINE];
    while(1)
    {
        bzero(&req, MAXLINE);
        int n=read(clientfd, &req , MAXLINE-1);
        if(n<=0) break;
        req[n]='\0';
        cout<<"request received :"<<clientfd<<" "<<req<<endl;
        sprintf(res , "response from server for user %d " , clientfd);
        printf("response send: %s"  , res);
        write(clientfd, res , strlen(res));
    }
    close(clientfd);
    return nullptr;
}


int main()
{
    int serverfd, clientfd;
    struct sockaddr_in saddr , caddr;
    //  res , req char arrays 
    cout<<"server started"<<endl;

    if((serverfd=socket(AF_INET , SOCK_STREAM , 0))<0){
        perror("socket related issues");
        exit(1);
    }
    
    
    //  to handle the binded address already in use problem - to free the address 
        
    int opt = 1;
setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));


    socklen_t len=sizeof(saddr);
    bzero(&saddr, len);
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(PORT);
    saddr.sin_addr.s_addr=htonl(INADDR_ANY);
    len=sizeof(saddr);
    if(bind(serverfd, (SA*)&saddr , len)<0){
        perror("bind");
        exit(1);
    }


    if(listen(serverfd, 5)<0){
        perror("listening error");
        exit(0);
    }
    while(1)
    {
        len=sizeof(caddr);
        bzero(&caddr , len);
        len=sizeof(caddr);
        clientfd=accept(serverfd, (SA*) &caddr , &len);
        if(clientfd<0){
            perror("accept error");
            exit(1);
        }
        int *cfd=new int(clientfd);
        pthread_t pid;
        pthread_create(&pid , nullptr  , handler , (void *)cfd );
        pthread_detach(pid);
    }
    exit(0);
}