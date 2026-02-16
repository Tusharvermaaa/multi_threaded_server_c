#include<bits/stdc++.h>

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/ioctl.h>

#include<signal.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<errno.h>

#define PORT 8080
#define SA struct sockaddr
#define MAXLINE 2048
using namespace std;
int main(int argc, char **argv)
{
    int serverfd, clientfd ;
    struct sockaddr_in saddr , caddr;
    char req[MAXLINE] , res[MAXLINE];
    if(argc!=2){
        perror("arguments :  server ip not passed ");
        exit(1);
    }

    if((clientfd=socket(AF_INET , SOCK_STREAM , 0 ))<0){
        perror("socket not created ");
        exit(1);
    }

    socklen_t len=sizeof(saddr);
    bzero(&saddr, len );
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(PORT);
    // saddr.sin_addr.s_addr
    int ipton=inet_pton(AF_INET , argv[1] , &saddr.sin_addr );
    if(ipton==0){
        perror("invalid address error"); exit(1);
    }
    else if(ipton<0){
        perror("invalid address error");
        exit(1);
    }
    len=sizeof(saddr);

    if(connect(clientfd, (SA*)&saddr , len)<0)
    {
        perror("connection f");
        exit(1);
    }
    cout<<"sussessfully connected to the server 😊"<<endl;
    while(1)
    {
        bzero(&req , MAXLINE);
        cout<<"enter your query: ";
        fgets(req, MAXLINE , stdin);
        string reqstr(req);
        if(reqstr=="exit\n"){
            break;
        }
        write(clientfd, req, strlen(req));
        bzero(&res, MAXLINE);
        int n;
        n=read(clientfd  ,&res , MAXLINE-1);
        if(n<=0) break;
        res[n]='\0';
        printf("Response from server : %s \n" , res);
    }
    close(clientfd);
    exit(0);
}