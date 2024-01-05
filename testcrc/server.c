#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h> 
void calccrc(char data[],char divisor[],char codeword[])
{
int datalen=strlen(data);
int divisorlen=strlen(divisor);
strcpy(codeword,data);
for(int i=0;i<=datalen-divisorlen;i++)
if(codeword[i]=='1')
for(int j=0;j<divisorlen;j++)
codeword[j+i]=(codeword[j+i]==divisor[j])?'0':'1';

}
int main()
{
int server_socket,client_socket;
struct sockaddr_in server_addr,cli_addr;
socklen_t addrsize=sizeof(cli_addr);
if((server_socket=socket(AF_INET,SOCK_STREAM,0))<0)
{
perror("error creating socket");
exit(0);
}
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(12345);
server_addr.sin_addr.s_addr=inet_addr("192.168.136.38");
if((bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))<0)
{
perror("error binding");
exit(0);
}
if((listen(server_socket,5))<0)
{
perror("error listening");
exit(0);
}
if((client_socket=accept(server_socket,(struct sockaddr*)&cli_addr,&addrsize))<0)
{
perror("errorn accepting connection");
exit(0);
}
char data[28];
char divisor[10];
char codeword[28];
read(client_socket,data,28);
read(client_socket,divisor,10);
calccrc(data,divisor,codeword);
write(client_socket,codeword,28);
printf("codeword sent to client %s\n",codeword);
close(client_socket);
close(server_socket);
return 0;

}
