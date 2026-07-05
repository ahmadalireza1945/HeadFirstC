#include <stdio.h>

enum response_type {DUMP, SECOND_CHANCE, MARIAGGE};
typedef struct {
    char* name;
    enum response_type type;
} response;

void dump(response r) {  printf("Dear %s,\n", r.name);
    puts("Unfortunately your last date contacted us to");
    puts("say that they will not be seeing you again");
}
void second_chance(response r) {
    printf("Dear %s,\n", r.name);
    puts("Good news: your last date has asked us to");
    puts("arrange another meeting. Please call ASAP.");
}
void marriage(response r) {
    printf("Dear %s,\n", r.name);
    puts("Congratulations! Your last date has contacted");
    puts("us with a proposal of marriage.");
}
void (*replies[])(response) = {dump, second_chance, marriage};

int main(int argc, char *argv[]) {
    response r[] = {
        {"mike", DUMP} ,{"luis", SECOND_CHANCE},
        {"matt", SECOND_CHANCE}, {"wiliam", MARIAGGE},
    };


    for (int i = 0; i < sizeof(r)/sizeof(r[0]); i++) {
        (replies[r[i].type])(r[i]);
    }
    return 0;
}
