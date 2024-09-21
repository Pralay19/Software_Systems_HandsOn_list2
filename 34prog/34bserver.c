/* 
====================================
* PROGRAM: 34bserver.c
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
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void* processClient(void* arg) {
    int clientConn = *((int*)arg);
    char clientBuffer[1024];
    memset(clientBuffer, 0, sizeof(clientBuffer));

    // Receive data from client
    recv(clientConn, clientBuffer, sizeof(clientBuffer), 0);
    printf("Client message: %s\n", clientBuffer);

    // Respond to client
    const char* serverMessage = "Hello from the server!";
    send(clientConn, serverMessage, strlen(serverMessage), 0);

    // Close client connection
    close(clientConn);
    free(arg);  // Free the memory allocated for client socket
    pthread_exit(NULL);
}

int main() {
    // Create server socket
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Allow socket to reuse the address
    int reuseOpt = 1;
    if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &reuseOpt, sizeof(reuseOpt)) == -1) {
        perror("setsockopt failed");
        close(serverSock);
        exit(EXIT_FAILURE);
    }

    // Bind the server socket
    if (bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Binding failed");
        close(serverSock);
        exit(EXIT_FAILURE);
    }

    // Start listening for client connections
    if (listen(serverSock, 5) == -1) {
        perror("Listening failed");
        close(serverSock);
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Allocate memory to handle client socket
        int* clientSock = malloc(sizeof(int));
        if (!clientSock) {
            perror("Memory allocation failed");
            continue;
        }

        *clientSock = accept(serverSock, NULL, NULL);
        if (*clientSock == -1) {
            perror("Accept failed");
            free(clientSock);
            continue;
        }

        pthread_t clientThread;
        // Create a new thread to handle the client connection
        if (pthread_create(&clientThread, NULL, processClient, clientSock) != 0) {
            perror("Thread creation failed");
            free(clientSock);
            continue;
        }

        // Detach the thread to clean up resources automatically
        pthread_detach(clientThread);
    }

    // Close the server socket
    close(serverSock);
    return 0;
}
