#include <stdio.h>

int main(int argc, char *argv[]) {
    float latitude, longitude;
    char info[80];
    int start = 0;

    puts("var data = [");
    while (scanf("%f, %f, %79[^\n]", &latitude, &longitude,info) == 3 ) {
        if (start)
            printf(",\n");
        else
            start = 1;

        if ((latitude < -90.0) || (latitude > 90.0)) {
            fprintf(stderr,"error: latitude out of range\n");
            return 2;
        }
        if ((longitude < -180.0) || (longitude > 180.0)) {
            fprintf(stderr,"error: longitude out of range\n");
            return 2;
        }
        printf("{\"latitude\": %f, \"longitude\": %f, \"info\": \"%s\"}", latitude, longitude, info);
    }
    puts("\n]");
    return 0;
}
