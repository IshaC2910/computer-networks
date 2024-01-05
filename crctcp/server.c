#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h> 

void calculateCRC(char data[], char divisor[], char codeword[]) {
    // Length of data and divisor
    int dataLength = strlen(data);
    int divisorLength = strlen(divisor);

    // Copy the data into the codeword
    strcpy(codeword, data);

    // Perform CRC division
    for (int i = 0; i <= dataLength - divisorLength; i++) {
        if (codeword[i] == '1') {
            for (int j = 0; j < divisorLength; j++) {
                codeword[i + j] = (codeword[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);
	char ip[]="192.168.136.38";
    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);  // Port number
    serverAddr.sin_addr.s_addr = inet_addr(ip); // Listen on all available network interfaces

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        perror("Listening failed");
        exit(1);
    }

    printf("Server is waiting for connections...\n");

    // Accept a connection from the client
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
    if (clientSocket == -1) {
        perror("Accepting connection failed");
        exit(1);
    }

    // Receive data and divisor from the client
    char data[28];
    char divisor[10];
    char codeword[28];

    read(clientSocket, data, sizeof(data));
    read(clientSocket, divisor, sizeof(divisor));

    // Calculate the CRC codeword
    calculateCRC(data, divisor, codeword);

    // Send the codeword back to the client
    write(clientSocket, codeword, sizeof(codeword));

    printf("Codeword sent to the client: %s\n", codeword);

    // Close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
