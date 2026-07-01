#include <stdio.h>

float total = 0.0;
int count = 0;
// tax_percent can be modified if needed
short tax_percent = 6;

// Function declaration
float add_with_tax(float val);

int main(int argc, char *argv[]) {
    float val;
    printf("Price of item: ");
    while (scanf("%f", &val) == 1) {
        printf("Total so far: %.2f\n", add_with_tax(val));
        printf("Price of item: ");
    }
    printf("\nFinal total: %.2f\n", total);
    printf("Number of items: %i\n", count);
    return 0;
}

float add_with_tax(float val) {
    float tax_rate = 1 + tax_percent / 100.0;
    total = total + (val * tax_rate);
    count++;
    return total;
}