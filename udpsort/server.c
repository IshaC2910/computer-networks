#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
// Driver code
void sort(int arr[],int n)
{
for(int i=0;i<n;i++)
for(int j=0;j<=i;j++)
if(arr[j]>arr[i])
{
int temp=arr[i];
arr[i]=arr[j];
arr[j]=temp;
}
for(int i=0;i<n;i++)
printf("%d ",arr[i]);
}
int main() {
int sockfd;
int arr[MAXLINE];
int n;

struct sockaddr_in servaddr, cliaddr;
// Creating socket file descriptor
if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));
memset(&cliaddr, 0, sizeof(cliaddr));
// Filling server information
servaddr.sin_family = AF_INET; // IPv4
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);
// Bind the socket with the server address
if ( bind(sockfd, (const struct sockaddr *)&servaddr,
sizeof(servaddr)) < 0 )
{
perror("bind failed");
exit(EXIT_FAILURE);
}
int len, sort_len;
len = sizeof(cliaddr); //len is value/resuslt
n = recvfrom(sockfd, (int *)arr, MAXLINE*sizeof(int),
MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
sort_len=n/sizeof(int);
sort(arr,sort_len);

sendto(sockfd, (const int *)arr, sort_len*sizeof(int),
MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
len);
printf("Sorted array sent back to the client\n");
return 0;
}
