
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int width;
    int height;
} rectangle;

int compare_areas(const void* a, const void* b) {
    rectangle* r1 = (rectangle*) a;
    rectangle* r2 = (rectangle*) b;
    int area1 = (r1->width * r1->height);
    int area2 = (r2->width * r2->height);
    return area1 - area2;
}

int compare_names(const void* a, const void* b) {
    char** a1 = (char**) a;
    char** a2 = (char**) b;
    return strcmp(*a1, *a2);
}

int main(int argc, char *argv[]) {
    rectangle rect;
    rect.width = 100;
    rect.height = 50;
    void* reac1 = &rect;
    printf("%d %d\n", rect.width, rect.height);
    qsort(reac1, 3, sizeof(rectangle), compare_areas);
    printf("%d %d\n", rect.width, rect.height);

    char *names[] = {"Karen", "Mark", "Brett", "Molly"};
    qsort(names, 4, sizeof(char *), compare_names);
    for (int i = 0; i < 4; i++) {
        printf("%s\n", names[i]);
    }
}
