#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h> 

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);  // Port number
    serverAddr.sin_addr.s_addr = inet_addr("192.168.136.38");  // Replace with the server's IP address

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // Input data and divisor
    char data[28];
    char divisor[10];

    printf("Enter data to be transmitted: ");
    scanf("%s", data);

    printf("Enter the divisor polynomial: ");
    scanf("%s", divisor);

    // Send data and divisor to the server
    write(clientSocket, data, sizeof(data));
    write(clientSocket, divisor, sizeof(divisor));

    // Receive and print the codeword from the server
    char codeword[28];
    read(clientSocket, codeword, sizeof(codeword));
    printf("Received codeword: %s\n", codeword);

    // Close the socket
    close(clientSocket);

    return 0;

}
