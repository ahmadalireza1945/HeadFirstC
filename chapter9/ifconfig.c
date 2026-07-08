#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // if (execl("/sbin/ifconfig","/sbin/ifconfig", NULL) == -1) {
    //     if (execlp("ipconfig", "ipconfig",NULL) == -1) {
    //         fprintf(stderr, "cannot run configip %s\n", strerror(errno));
    //     }
    // }

    char buffer[500];
    char output[1500];
    FILE *pipe;
    int is_first_line = 1;

    pipe = popen("/bin/ifconfig", "r");

    if (pipe == NULL || fgets(buffer, sizeof(buffer), pipe) == NULL) {
        if (pipe != NULL) pclose(pipe);

        pipe = popen("ipconfig", "r");
        if (pipe == NULL) {
            fprintf(stderr, "Can't open ipconfig\n",strerror(errno));
            return -1;
        }
    }else {
        is_first_line = 0;
    }

if (!is_first_line) {
    printf("%s", buffer);
    strcat(output, buffer);
}
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);

        if (strlen(output) + strlen(buffer) < sizeof(output) -1 ) {
            strcat(output, buffer);
        }
    }
    pclose(pipe);


    FILE *file_ptr = fopen("ip.txt", "w");
    if (file_ptr == NULL) {
        fprintf(stderr, "Can't open ip.txt\n",strerror(errno));
        return -1;
    }

    fprintf(file_ptr, "%s", output);
    fclose(file_ptr);
    printf("berhasil");
    return 0;

}
