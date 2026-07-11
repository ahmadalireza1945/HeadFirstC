#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h> // Diperlukan untuk strncasecmp pada beberapa sistem

#define BUFF_SIZE 1024

void error(char *message) {
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(1);
}

int openlistenersocket() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        error("socket error");
    }
    return s;
}

void bind_to_port(int socket, int port) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = (in_port_t)htons(port); // Menggunakan argumen port (3000)
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) < 0) {
        error("setsockopt");
    }

    int c = bind(socket, (struct sockaddr *)&address, sizeof(address));
    if (c < 0) {
        error("bind");
    }
}

int say(int socket, char *message) {
    int result = send(socket, message, strlen(message), 0);
    if (result < 0) {
        error("send");
    }
    return result; // PERBAIKAN 2: Harus mengembalikan nilai result
}

// Fungsi pembaca input modifikasi agar lebih aman menghapus \r dan \n
int read_line(int socket, char *buff, int len) {
    memset(buff, 0, len);
    int c = recv(socket, buff, len - 1, 0);
    if (c <= 0) return c;
    
    // Hilangkan karakter newline di ujung string agar komparasi mudah
    while(c > 0 && (buff[c-1] == '\n' || buff[c-1] == '\r')) {
        buff[c-1] = '\0';
        c--;
    }
    return c;
}

int main(int argc, char *argv[]) {
    char buffer[BUFF_SIZE] = {0};
    int listener_d = openlistenersocket();
    bind_to_port(listener_d, 3000);

    if (listen(listener_d, 10) < 0) {
        error("listen");
    }

    // Menghilangkan \r\n dari master string agar pencocokan string murni teks bebas gangguan
    char *message[] = {
        "knock knock\r\n",
        "Who's there?",
        "oscar\r\n",
        "oscar who?",
        "oscar silly question, you get a silly answer\r\n",
    };

    printf("Server berjalan di port 3000...\n");

    struct sockaddr_storage client;
    unsigned int addrlen = sizeof(client);
    int s = accept(listener_d, (struct sockaddr *)&client, &addrlen);

    while (1) {

        if (s < 0) {
            error("accept");
        }
        
        // Mulai permainan
        say(s, message[0]);

        // Tahap 1: Menunggu "Who's there?"
        if (!fork()) {
            close(listener_d);
            if (read_line(s, buffer, sizeof(buffer)) > 0) {
                if (strcasecmp(buffer, message[1]) != 0) {
                    say(s, "You should say: Who's there?\r\n");
                } else {
                    // Tahap 2: Mengatakan "oscar"
                    say(s, message[2]);
                    if (read_line(s, buffer, sizeof(buffer)) > 0) {
                        if (strcasecmp(buffer, message[3]) != 0) {
                            say(s, "You should say: oscar who?\r\n");
                        } else {
                            // Tahap 4: Memberikan punchline
                            say(s, message[4]);
                        }
                    }
                }
            }
            close(s);
            exit(0);
        }
        close(s);
    }
    return 0;
}
