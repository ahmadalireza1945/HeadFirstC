#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    char *advice[] = {
        "Take smaller bites\r\n",
        "Go for the tight jeans. No they do NOT make you look fat.\r\n",
        "One word: inappropriate\r\n",
        "Just for today, be honest. Tell your boss what you *really* think\r\n",
        "You might want to rethink that haircut\r\n" };

    //buat socket

    char buffer[BUFFER_SIZE] = {0};
    int listener_d;
    if ((listener_d = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    //bind socket
    struct sockaddr_in server;
    server.sin_family = PF_INET;
    server.sin_port = (in_port_t)htons(3000);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listener_d, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("bind");
    }

    int reuse = 1;
    if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1) {
        perror("setsockopt");
    }
    //listen socket
    int listen1 = listen(listener_d, 5);
    if (listen1 == -1) {
        perror("listen");
    }

    //accept
    while (1) {
        struct sockaddr_storage client;
        unsigned int addrlen = sizeof(client);
        int connect_d = accept(listener_d, (struct sockaddr *)&client, &addrlen);
        char *msg = advice[rand() % 5];

        //send
        send(connect_d, msg, strlen(msg), 0);

        while (1) {

        memset(buffer, '\0', BUFFER_SIZE);

        ssize_t bytes_read = recv(connect_d, buffer, BUFFER_SIZE - 1, 0);

            if (bytes_read <= 0) {
                if (bytes_read < 0) {
                    perror("recv error");
                } else {
                    printf("Client disconnected.\n");
                }
                close(connect_d);
                break; // Break inner loop to accept the next client
            }

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the string safely
            printf("Received from client: %s\n", buffer);

            // 6. SEND BACK THE INPUT DATA TO THE CLIENT
            // Use send() to transmit the buffer contents back over the client socket
            ssize_t bytes_sent = send(connect_d, buffer, strlen(buffer), 0);

            if (bytes_sent < 0) {
                perror("Failed to send data back");
            } else {
                printf("Successfully echoed %ld bytes back to client.\n", bytes_sent);
            }

            if (memcmp(buffer, "exit",4) == 0) {
                close(connect_d);
                break;
            }

        }

        }

    }
    return 0;

}