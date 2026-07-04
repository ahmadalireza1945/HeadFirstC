#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island {
    char *name;
    char *open;
    char *close;
    struct island *next;
}island;

void display(island *head) {
    for (island *i = head;i != NULL; i = i->next) {
        printf("this name : %s open %s close : %s\n ", i->name, i->open, i->close);
    }
}

island* create(char *name) {
    island *i = malloc(sizeof(island));
    i->name = strdup(name);
    i->open = "07:00";
    i->close = "19:00";
    i->next = NULL;
    return i;
}

int main(int argc, char *argv[]) {

    char name[80];
    fgets(name, 80, stdin);
    island *island1 = create(name);
    display(island1);
    fgets(name, 80, stdin);
    island *island2 = create(name);
    display(island2);


    /*island madura = {"madura", "09:00","10:00",NULL};
    island jawa = {"jawa", "09:00","10:00",NULL};
    island kalimantan = {"kalimantan", "09:00","10:00",NULL};

    madura.next = &jawa;
    jawa.next = &kalimantan;

    display(&madura);*/

}
