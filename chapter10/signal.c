#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void die(int sig) {
    puts("good bye bitch");
    exit(1);
}

int cacth_signal(int sig, void (*handler)(int) ) {
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask); 
    act.sa_flags = 0;
    return sigaction(sig, &act, NULL);
}

int main() {
    if (cacth_signal(SIGINT, die) == -1) {
        fprintf(stderr, "can't cacth SIGINT\n");
        exit(2);
    }

    char name[30];
    printf("enter your name : ");
    fgets(name, 30, stdin);
    printf("your name is : %s\n", name);
    return 0;
}
