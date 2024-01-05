#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<time.h>
#include<unistd.h>
#define PORT 12345
#define MAX 1024
#define IP "192.168.136.38"
int main()
{
int client_socket;
struct sockaddr_in server_addr;
char buffer[MAX];
if((client_socket=socket(AF_INET,SOCK_STREAM,0))<0)
{
perror("error creating socket");
exit(0);
}
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(PORT);
server_addr.sin_addr.s_addr=inet_addr(IP);
if((connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))<0)
{
perror("connecting error");
exit(0);
}
memset(buffer,0,sizeof(buffer));
recv(client_socket,buffer,sizeof(buffer),0);
printf("date and time recieved from server:%s\n",buffer);
close(client_socket);
return 0;
}
