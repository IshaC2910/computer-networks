#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>
void main(int argc,char* argv[]){
int clifd,cli_len,connect_cli=0,write_to,read_from;
char bufferc[256];
struct sockaddr_in servaddr;
if(clifd<0){
printf("error\n");
exit(1);
}
bzero((char*)&servaddr,sizeof(servaddr));
int port=7;
servaddr.sin_family=AF_INET;
if(argc<2)
{
printf("usage:./udpclient2 192.168.10.1");
exit(1);
}
servaddr.sin_addr.s_addr=inet_addr(argv[1]);
servaddr.sin_port=htons(port);
bzero(bufferc,sizeof(bufferc));
printf("enter a message\n");
fgets(bufferc,sizeof(bufferc),stdin);
int serv_size=sizeof(servaddr);
if(sendto(clifd,bufferc,sizeof(bufferc),0,(struct sockaddr*)&servaddr,serv_size)<0)
{
printf("error sending");
exit(1);
}
bzero(bufferc,sizeof(bufferc));
if(recvfrom(clifd,bufferc,sizeof(bufferc),0,(struct sockaddr*)&servaddr,&serv_size)<0){
printf("error recieving");
exit(1);
}
printf("client recieved from server:%s\n",bufferc);
close(clifd);
exit(0);
}

