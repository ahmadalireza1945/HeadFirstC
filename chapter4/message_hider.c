#include <stdio.h>
#include "encrypt.h"

int main(int argc, char *argv[]) {
    char val[80];
    while (fgets(val, 80, stdin) != NULL) {
        encrypt(val);
        printf("%s\n", val);
        printf("after decrypt\n");
        decrypt(val);
        printf("%s\n", val);
    }
}
