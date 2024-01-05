#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
int main(int argc,char* argv[])
{
int sockfd,data_ch,option=1,sizeserv_addr,incoming_len,ret_bind,ret_listen,ret_read,ret_write,port=7;
char buffers[256];
char ip_string[]="192.168.136.38";
struct sockaddr_in servaddr,incoming;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
bzero((char*)&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr(ip_string);
servaddr.sin_port=htons(port);
if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
{
printf("error:cannot bind\n");
exit(1);
}
incoming_len=sizeof(incoming);
printf("UDP server waiting\n");
bzero((char*)buffers,sizeof(buffers));
if(recvfrom(sockfd,buffers,sizeof(buffers),0,(struct sockaddr*)&incoming,&incoming_len)<0)
{
printf("error receiving from client..\n");
exit(1);
}
printf("server recieved from client:%s\n",buffers);
if(sendto(sockfd,buffers,sizeof(buffers),0,(struct sockaddr*)&incoming,sizeof(incoming))<0)
{
printf("error sending to client\n");
exit(1);
}
close(sockfd);
return 0;
}
