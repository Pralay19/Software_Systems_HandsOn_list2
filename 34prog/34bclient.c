/* 
====================================
* PROGRAM: 34bclient.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to create a concurrent server.
b. use pthread_create
====================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // Create the client socket
    int clientConn = socket(AF_INET, SOCK_STREAM, 0);
    if (clientConn == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Attempt to connect to the server
    if (connect(clientConn, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection to server failed");
        close(clientConn);
        exit(EXIT_FAILURE);
    }

    // Send message to the server
    const char* clientMessage = "Hello from the client!";
    send(clientConn, clientMessage, strlen(clientMessage), 0);

    // Receive response from the server
    char serverResponse[1024];
    memset(serverResponse, 0, sizeof(serverResponse));  // Clear the buffer
    recv(clientConn, serverResponse, sizeof(serverResponse), 0);
    printf("Server response: %s\n", serverResponse);

    // Close the client socket
    close(clientConn);
    return 0;
}
