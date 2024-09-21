/* 
====================================
* PROGRAM: 34aserver.c
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

void processClientRequest(int clientConn) {
    char clientBuffer[1024];
    memset(clientBuffer, 0, sizeof(clientBuffer));

    // Receive data from the client
    recv(clientConn, clientBuffer, sizeof(clientBuffer), 0);
    printf("Message from client: %s\n", clientBuffer);

    // Send a response back to the client
    const char* serverMessage = "Greetings from the server!";
    send(clientConn, serverMessage, strlen(serverMessage), 0);

    // Close client connection
    close(clientConn);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Reuse the address to avoid issues with TIME_WAIT
    int reuseOption = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuseOption, sizeof(reuseOption)) == -1) {
        perror("Set socket options failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming client connections
    if (listen(serverSocket, 5) == -1) {
        perror("Listen failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    printf("Server Online...\n");

    while (1) {
        // Accept a connection from a client
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            perror("Client connection failed");
            exit(EXIT_FAILURE);
        }

        // Create a child process to handle the client request
        if (fork() == 0) {
            close(serverSocket);  // Child doesn't need to listen for more connections
            processClientRequest(clientSocket);
            exit(0);
        } else {
            close(clientSocket);  // Parent closes the client connection
        }
    }

    // Close the server socket
    close(serverSocket);
    return 0;
}
