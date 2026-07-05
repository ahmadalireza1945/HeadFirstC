#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    // Cast void pointers to integer pointers and dereference them
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    // Return negative if a < b, positive if a > b, 0 if equal
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;

    // Shortcut for ascending order: return (arg1 - arg2);
    // Shortcut for descending order: return (arg2 - arg1);
}

int main(int argc, char *argv[]) {
    int i[] = {42, 7, 89, 23, 11, 56, 4, 92, 31, 15};
    int size = sizeof(i) / sizeof(i[0]);

    for (int x = 0; x < size; x++) {
        printf("%i ,",i[x]);
    }

    puts("\n");
        qsort(i, size, sizeof(int), compare_ints);

    for (int x = 0; x < size; x++) {
        printf("%i ,",i[x]);
    }
    printf("%zu\n", sizeof(int) * size);

    return 0;
}
