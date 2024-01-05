#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h> 
int main()
{
int client_socket;
struct sockaddr_in server_addr;
if((client_socket=socket(AF_INET,SOCK_STREAM,0))<0)
{
perror("socket error");
exit(0);
}
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(12345);
server_addr.sin_addr.s_addr=inet_addr("192.168.136.38");
if((connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))<0)
{
perror("error connecting");
exit(0);
}
char data[28];
char divisor[10];
char codeword[28];
printf("enter data to be transmitted");
scanf("%s",data);
printf("entr divisor");
scanf("%s",divisor);
write(client_socket,data,28);
write(client_socket,divisor,10);
read(client_socket,codeword,28);
printf("recieved codeword %s for data %s \n",codeword,data);
close(client_socket);
return 0;

}
