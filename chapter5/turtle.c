#include <stdio.h>
typedef struct {
    char *name;
    char *spesis;
    int age;
} turtle;

void happy_turtle(turtle *t) {
    (*t).age = (*t).age + 1;
    printf("happy birtday turtle your age : %i name : %s and spesies : %s\n", t->age, t->name, t->spesis);
}

int main(int argc, char *argv[]) {
    turtle reza = {"reza", "idk", 99};
    happy_turtle(&reza);
    printf("happy birtday turtle your age : %i name : %s and spesies : %s\n", reza.age, reza.name, reza.spesis);
    return 0;
}
