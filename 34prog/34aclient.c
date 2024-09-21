/* 
====================================
* PROGRAM: 34aclient.c
* AUTHOR: PRALAY D. SAW
* ROLLNO: MT2024119
* DESCRIPTION:
Write a program to create a concurrent server.
a. use fork
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
        perror("Failed to create client socket");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Establish connection to the server
    if (connect(clientConn, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Connection to server failed");
        close(clientConn);
        exit(EXIT_FAILURE);
    }

    // Send a message to the server
    const char* clientMessage = "Greetings from the client";
    send(clientConn, clientMessage, strlen(clientMessage), 0);

    // Receive response from the server
    char serverResponse[1024];
    memset(serverResponse, 0, sizeof(serverResponse));
    recv(clientConn, serverResponse, sizeof(serverResponse), 0);
    printf("Server reply: %s\n", serverResponse);

    // Close the client socket
    close(clientConn);
    return 0;
}
