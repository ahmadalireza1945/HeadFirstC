#include <stdarg.h>
#include <stdio.h>

enum type_of_drink{ALE, KOPI, KERATINDENG, ARAK, ALKOHOL};

double price(enum type_of_drink d) {
    switch (d) {
        case ALE:
            return 1.5;
        case KOPI:
            return 2.0;
        case KERATINDENG:
            return 3.0;
        case ARAK:
            return 4.0;
        case ALKOHOL:
            return 5.0;
    }
    return 0;
}

double total(int args, ...) {
    double total = 0;
    va_list ap;
    va_start(ap, args);
    int i;
    for (i = 0 ; i < args; i++) {
        enum type_of_drink d = va_arg(ap, enum type_of_drink);
        total = total + price(d);
    }
    va_end(ap);
    return total;
}

int main(int argc, char *argv[]) {
    printf("total nya : %.2f\n",total(7,ARAK,ALE,KOPI,KERATINDENG));
}
