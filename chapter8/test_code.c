#include <stdio.h>
#include "checksum.h"
#include "encrypt.h"

int main(int argc, char *argv[]) {
    char message[] = "nama saya adalah ahmad ali reza";
    encrypt(message);
    printf("'%s'\n", message);
    printf("%i\n", checksum(message));
    decrypt(message);
    printf("'%s'\n", message);
    printf("%i\n", checksum(message));
    return 0;
}