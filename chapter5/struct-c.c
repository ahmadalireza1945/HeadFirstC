#include <stdio.h>

struct fish {
    const char *name;
    const char *spesies;
    int teeth;
    int age;
};

void label(struct fish f) {
    printf("this is :%s, and spesies from : %s and teeth : %i and age : %i\n",
            f.name, f.spesies, f.teeth, f.age
    );
}

int main(int argc, char *argv[]) {


    struct fish f = {"piranha","fish",5,200};

    label(f);
}
