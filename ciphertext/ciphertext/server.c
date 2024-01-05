#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// Function to perform Caesar cipher encryption
char* caesarCipher(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + shift) % 26 + base;
        }
    }
    return text;
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, clientaddr;
    socklen_t len = sizeof(clientaddr);

    // Create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Server address setup
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8001);
    servaddr.sin_family = AF_INET;

    // Bind the socket
    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    char buffer[256];

    while (1) {
        printf("UDP Server waiting for a message...\n");

        // Receive a message from the client
        int n = recvfrom(sockfd, (char*)buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &len);
        if (n < 0) {
            perror("Error receiving from client");
            exit(1);
        }

        buffer[n] = '\0';
        printf("Server received from client: %s\n", buffer);

        // Encrypt the message
        char* ciphertext = caesarCipher(buffer, 3);
        printf("Server encrypted the message: %s\n", ciphertext);

        // Send the cipher text back to the client
        sendto(sockfd, ciphertext, strlen(ciphertext), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
        printf("Server sent cipher text to client: %s\n", ciphertext);
    }

    close(sockfd);

    return 0;
}

