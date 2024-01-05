#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<time.h>
#include<unistd.h>
#define PORT 12345
#define MAX 1024
int main()
{
int server_socket,client_socket;
struct sockaddr_in server_addr,cli_addr;
socklen_t cli_addr_len=sizeof(cli_addr);
char buffer[MAX];
if((server_socket=socket(AF_INET,SOCK_STREAM,0))<0)
{
perror("error creating socket");
exit(0);
}
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(PORT);
server_addr.sin_addr.s_addr=INADDR_ANY;
if((bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))==-1)
{
perror("error binding");
exit(0);
}
if(listen(server_socket,5)<0)
{
perror("error listening");
exit(1);
}
printf("server listening to port %d...\n",PORT);
while(1)
{
if((client_socket=accept(server_socket,(struct sockaddr*)&cli_addr,&cli_addr_len))==-1)
{
perror("error accepting connection");
exit(0);
}
time_t raw_time;
struct tm* time_info;
time(&raw_time);
time_info=localtime(&raw_time);
strftime(buffer,sizeof(buffer),"%Y-%m-%d %h:%M:%S",time_info);
send(client_socket,buffer,sizeof(buffer),0);
printf("sent date and time to the client %s\n",buffer);
close(client_socket);
}
close(server_socket);
return 0;

}
