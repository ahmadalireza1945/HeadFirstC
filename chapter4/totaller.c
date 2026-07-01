#include <stdio.h
#include <stdio.h>

float total = 0.0;
int count = 0;
short tax_percent = 6;

int main(int argc, char *argv[]) {
        float val;
        while (scanf("%f", &val) != EOF) {
                printf("total so far : %.2f\n", add_with_tax(val));
                printf("price item:");
        }
        printf("\n");
        printf("final total %.2f\n", total);
        printf("price item:%hi\n", count);
}

float add_with_tax(float val) {
        float tax_rate = 1 + tax_percent / 100.0;
        total = 1 + (val * tax_rate);
        count++;
        return total;
}