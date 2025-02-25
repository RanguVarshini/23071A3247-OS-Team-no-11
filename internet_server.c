#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define INTERNET_PORT 12345
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 4

void *handle_client(void *socket_desc) {
    int sock = (int)socket_desc;
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';
        printf("Client: %s\n", buffer);
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);
    }

    close(sock);
    free(socket_desc);
    return NULL;
}

void start_internet_server() {
    int server_fd, client_sock;
    struct sockaddr_in server, client;
    socklen_t client_size = sizeof(client);
    pthread_t client_threads[MAX_CLIENTS];
    int client_count = 0;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(INTERNET_PORT);
    
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        exit(1);
    }
    
    listen(server_fd, MAX_CLIENTS);
    printf("Internet Socket Server listening on port %d...\n", INTERNET_PORT);
    
    while (client_count < MAX_CLIENTS && (client_sock = accept(server_fd, (struct sockaddr *)&client, &client_size))) {
        printf("Client connected.\n");
        int *new_sock = malloc(sizeof(int));
        *new_sock = client_sock;
        pthread_create(&client_threads[client_count++], NULL, handle_client, (void*)new_sock);
    }
    
    for (int i = 0; i < client_count; i++) {
        pthread_join(client_threads[i], NULL);
    }
    
    close(server_fd);
}

int main() {
    start_internet_server();
    return 0;
}
