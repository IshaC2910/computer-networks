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
int main() {
int sockfd;
int arr[MAXLINE];
int n;
struct sockaddr_in servaddr;
// Creating socket file descriptor
if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));
// Filling server information
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);
servaddr.sin_addr.s_addr =inet_addr("192.168.136.38");
int unsorted_arr[10];
int usort_len;
printf("enter len of array:");
scanf("%d",&usort_len);
for(int i=0;i<usort_len;i++)
{
scanf("%d",&unsorted_arr[i]);
}
sendto(sockfd, (const int*)unsorted_arr,usort_len* sizeof(int),
MSG_CONFIRM, (const struct sockaddr *) &servaddr,
sizeof(servaddr));
printf("Array sent to server for sorting.\n");
n = recvfrom(sockfd, (int*)arr, MAXLINE*sizeof(int),
MSG_WAITALL, (struct sockaddr *)NULL,NULL);
int sorted_len=n/sizeof(int);
printf("Sorted array:\n");
for(int i=0;i<sorted_len;i++)
{
printf("%d ",arr[i]);
}
printf("\n");
close(sockfd);
return 0;
} 
