/* 
====================================
* PROGRAM: 33server.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to communicate between two machines using socket.
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 8080
#define BACKLOG 3  // Number of pending connections allowed

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress;
    int addrLen = sizeof(serverAddress);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address struct
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(SERVER_PORT);

    // Bind socket to the address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, BACKLOG) == -1) {
        perror("Listen failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", SERVER_PORT);

    // Accept a connection from a client
    clientSocket = accept(serverSocket, (struct sockaddr *)&serverAddress, (socklen_t*)&addrLen);
    if (clientSocket == -1) {
        perror("Accept failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Receive message from client
    char buffer[1024] = {0};
    read(clientSocket, buffer, sizeof(buffer));
    printf("Received message: %s\n", buffer);

    // Close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
