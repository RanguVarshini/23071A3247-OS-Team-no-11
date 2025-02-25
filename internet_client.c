#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define INTERNET_HOST "127.0.0.1"
#define INTERNET_PORT 12345
#define BUFFER_SIZE 1024

void connect_internet_socket() {
    int sock;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(INTERNET_PORT);
    server.sin_addr.s_addr = inet_addr(INTERNET_HOST);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to Internet socket server on port %d.\n", INTERNET_PORT);

    while (1) {
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);

        if (recv(sock, buffer, BUFFER_SIZE, 0) <= 0) {
            perror("Server disconnected");
            break;
        }
        printf("Server: %s\n", buffer);
    }

    close(sock);
}

int main() {
    connect_internet_socket();
    return 0;
}
