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
int main()
{
int sockfd;
struct sockaddr_in server_addr;
int n,len,sort_len,arr[MAx];
if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
{
perror("error creatig socket");
exit(EXIT_FALIURE);
}
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(PORT);
server_addr.sin_addr.s_addr=inet_addr("192.168.136.38");
int usortlen,usort_arr[10];
printf("enter length of array:\n");
scanf("%d",&usortlen);
printf("enter array elements:\n");
for(int i=0;i<usortlen;i++)
{
scanf("%d",usort_arr[i]);
}
printf('\n');
sendto(sockfd,(const struct int*)usort_arr,usortlen*sizeof(int),MSG_CONFIRM,(const struct sockaddr*)&server_addr,sizeof(server_addr));
printf("unsorted array send to server\n");
n=recvfrom(sockfd,(struct sockaddr*)arr,MAX*sizeof(int),MSG_WAITALL,(struct sockaddr*)NULL,NULL);
sort_len=n/sizeof(int);
printf("sorted array:");
for(int i=0;i<sort_len;i++)
{
printf("arr[i]");
}
close(sockfd);
return 0;
}
