#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_SOCKET_PATH "/tmp/chat_socket"
#define BUFFER_SIZE 1024

void connect_unix_socket() {
    int sock;
    struct sockaddr_un server;
    char buffer[BUFFER_SIZE];

    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, SERVER_SOCKET_PATH);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to UNIX domain socket server.\n");

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
    connect_unix_socket();
    return 0;
}
