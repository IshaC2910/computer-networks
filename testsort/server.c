#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#define PORT 8002
#define MAX 1024
void sort(int arr[],int n)
{
for(int i=0;i<n;i++)
{
for(int j=0;j<=i;j++)
{
if(arr[j]>arr[i])
{
int t=arr[i];
arr[i]=arr[j];
arr[j]=t;
}
}
}
for(int i=0;i<n;i++)
printf("%d",arr[i]);
printf("\n");
}
int main()
{
int server_socket,client_socket;
struct sockaddr_in server_addr,client_addr;
int n,len,sort_len,arr[MAx];
if((server_socket=socket(AF_INET,SOCK_DGRAM,0))<0)
{
perror("error creatig socket");
exit(EXIT_FALIURE);
}
memset(&server_addr,0,sizeof(server_addr));
memset(&client_addr,0,sizeof(client_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(PORT);
server_addr.sin_addr.s_addr=INADDR_ANY;

if((bind(server_socket,(const struct sockaddr*)&server_addr,sizeof(server_addr)))<0)
{
perror("error binding socket");
exit(EXIT_FALIURE);
}
len=sizeof(vlient_addr);
n=rcvfrom(server_socket,(int*)arr,MAX*sizeof(int),MSG_WAITALL,(struct sockaddr*)&client_addr,&len);
sort_len=n/sizeof(int);
sort(arr,sort_len);
sendto(server_socket,(const int*)arr,sort_len*sizeof(int),MSG_CONFIRM,(const struct sockaddr*)&client_addr,len);
printf("sorted array sent to client\n");
close(server_socket);
return 0;

}
