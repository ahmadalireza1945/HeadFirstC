#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

void error(char *message) {
    fprintf(stderr, "%s", strerror(errno));
    exit(1);
}

int open_socket(char* host, char* port) {
    struct addrinfo hint;
    struct addrinfo *res;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port, &hint, &res)) {
        error("can't resolve local ip address");
    }
    int d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (d_sock == -1) {
        freeaddrinfo(res);
        error("could not create socket");
    }

    int c = connect(d_sock, res->ai_addr, res->ai_addrlen);
    if (c == -1) {
        close(d_sock);
        error("could not connect to the server");
    }
    return d_sock;
}

int say(int socket, char* message) {
    int result = send(socket, message, strlen(message), 0);
    if (result == -1) {
        error("could not send");
    }
    return result;
}

char* url_encode(const char *str) {
    const char *hex = "0123456789ABCDEF";
    size_t len = strlen(str);
    char *encoded = malloc(len * 3 + 1); // Max possible size
    char *p = encoded;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            *p++ = c;
        } else if (c == ' ') {
            *p++ = '+';
        } else {
            *p++ = '%';
            *p++ = hex[c >> 4];
            *p++ = hex[c & 15];
        }
    }
    *p = '\0';
    return encoded;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Gunakan: %s <nama_halaman_wikipedia>\n", argv[0]);
        return 1;
    }

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD *method = TLS_client_method();
    SSL_CTX *ctx = SSL_CTX_new(method);
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        error("Gagal membuat SSL Context");
    }

    int d_sock = open_socket("en.wikipedia.org","443");

    d_sock = open_socket("en.wikipedia.org", "443");

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, d_sock);

    SSL_set_tlsext_host_name(ssl, "en.wikipedia.org");

    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        error("Gagal melakukan SSL Handshake");
    }


    char buffer[1024];
    char *encode = url_encode(argv[1]);
    if (!encode) error("Gagal enkripsi URL");

    // KODE BARU (Menambahkan User-Agent wajib):
    sprintf(buffer,
        "GET /wiki/%s HTTP/1.1\r\n"
        "Host: en.wikipedia.org\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36\r\n"
        "Connection: close\r\n\r\n",
        encode);



    if (SSL_write(ssl, buffer, strlen(buffer)) <= 0) {
        error("Gagal mengirim data lewat SSL");
    }

    char rec[256];
    int ByteRcvd = SSL_read(ssl, rec, 255);
    while (ByteRcvd > 0) {
        rec[ByteRcvd] = '\0';
        printf("%s", rec);
        ByteRcvd = SSL_read(ssl, rec, 256);
    }
    free(encode);
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(d_sock);
    SSL_CTX_free(ctx);
    return 0;

}

