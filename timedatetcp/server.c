#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main(){
int server_socket,client_socket;
struct sockaddr_in server_addr,client_addr;
socklen_t client_addr_len=sizeof(client_addr);
char buffer[MAX_BUFFER_SIZE];
if((server_socket=socket(AF_INET,SOCK_STREAM,0))==-1){
perror("Error creating socket");
exit(1);
}
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(PORT);
server_addr.sin_addr.s_addr=INADDR_ANY;

if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1){
perror("Error binding");
exit(1);
}
if(listen(server_socket,5)==-1)
{
perror("Error listening");
exit(1);
}
printf("server listening on port %d....\n",PORT);
while(1)
{
if((client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&client_addr_len))==-1)
{
perror("Error accepting connection");
exit(1);
}
time_t raw_time;
struct tm *time_info;
time(&raw_time);
time_info=localtime(&raw_time);
strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",time_info);
send(client_socket,buffer,strlen(buffer),0);
printf("sent date and time to client:%s\n",buffer);
close(client_socket);
}
close(server_socket);
return 0;
}
