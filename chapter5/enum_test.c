#include <stdio.h>

typedef enum {
    COUNT, POUNDS, PINTS
} unit_of_measure;

typedef union {
    short count;
    float weight;
    float volume;
} quantity;

typedef struct {
    const char *name;
    const char *country;
    quantity amount;
    unit_of_measure measure;
} fruit_order;

void display(fruit_order fruit) {
    printf("this order contain :");

    if (fruit.measure == PINTS) {
        printf("%2.2f pints of %s\n", fruit.amount.volume, fruit.name);
    }else if (fruit.measure == POUNDS) {
        printf("%2.2f pounds of %s\n", fruit.amount.weight, fruit.name);
    }else {
        printf("%i count of %s\n", fruit.amount.count, fruit.name);
    }
}

int main(int argc, char *argv[]) {
    fruit_order apples = {"apples", "england", .amount.count=144,COUNT};
    fruit_order strabery = {"strabery", "indonesia", .amount.weight=17.6, POUNDS};
    fruit_order oj = {"oj", "singapore", .amount.volume=10.6, PINTS};

    display(apples);
    display(strabery);
    display(oj);
    return 0;
}
