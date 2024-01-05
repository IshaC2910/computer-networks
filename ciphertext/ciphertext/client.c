#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Function to perform Caesar cipher decryption
char* caesarDecipher(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base - shift + 26) % 26 + base;
        }
    }
    return text;
}

int main(int argc, char *argv[]) {
    
    int sockfd;
    struct sockaddr_in servaddr;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Server address setup
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_port = htons(8001);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.136.38");

    char buffer[256];

    printf("Enter a Message: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Send the message to the server
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("Client sent message to server: %s\n", buffer);

    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);

    // Receive the cipher text from the server
    int n = recvfrom(sockfd, (char*)buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &len);
    if (n < 0) {
        perror("Error receiving from server");
        exit(1);
    }

    buffer[n] = '\0';
    printf("Client received cipher text from server: %s\n", buffer);

    // Decrypt the cipher text
    char* plaintext = caesarDecipher(buffer, 3);
    printf("Client decrypted the message: %s\n", plaintext);

    close(sockfd);

    return 0;
}

