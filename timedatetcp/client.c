#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<arpa/inet.h>
#include<unistd.h>

#define SERVER_IP "192.168.136.38"
#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main(){
int client_socket;
struct sockaddr_in server_addr;
char buffer[MAX_BUFFER_SIZE];

if((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1){
perror("Error creating socket");
exit(1);
}
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(PORT);
server_addr.sin_addr.s_addr=inet_addr(SERVER_IP);

if(connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
{
perror("Error connecting to server");
exit(1);
}
memset(buffer,0,sizeof(buffer));
recv(client_socket,buffer,sizeof(buffer),0);

printf("recieved date and time from server:%s\n",buffer);
close(client_socket);
return 0;

}
