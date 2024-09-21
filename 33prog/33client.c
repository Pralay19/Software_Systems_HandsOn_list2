/* 
====================================
* PROGRAM: 33a.c
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
#include <sys/types.h>
#include <sys/socket.h>

#define SERVER_PORT 8080
#define SERVER_ADDRESS "127.0.0.1"

int main() {
    struct sockaddr_in serverAddress;
    int clientSocket;
    char *message = "Hello from client";

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);

    // Convert IPv4 address from text to binary
    if (inet_pton(AF_INET, SERVER_ADDRESS, &serverAddress.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Connection failed");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // Send message to the server
    send(clientSocket, message, strlen(message), 0);
    printf("Message sent: %s\n", message);

    // Close the socket
    close(clientSocket);

    return 0;
}
