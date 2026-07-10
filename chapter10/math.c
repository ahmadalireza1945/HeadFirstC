
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int score;

void end_game(int sig) {
        printf("\n Final score : %i\n",score);
        exit(1);
}

int catch_signal(int sig, void (*handler)(int)) {
        struct sigaction act;
        act.sa_handler = handler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        return sigaction(sig, &act, NULL);
}

void time_up(int sig) {
        puts("\nTime's up");
        raise(SIGINT);
}

void error(char *msg) {
        printf("\nERROR: %s\n", msg);
}

int main(int argc, char *argv[]) {
        catch_signal(SIGALRM, time_up);
        catch_signal(SIGINT, end_game);
        srandom(time(0));
        while (1) {
                int a = random() % 11;
                int b = random() % 11;
                char txt[4];
                alarm(5);
                printf("\nWhat is %i times %i? ",a, b);
                fgets(txt, 4, stdin);
                int answer = atoi(txt);
                if (answer == (a * b)) {
                        score++;
                }else
                        printf("\nWrong score %i\n", score);
        }
        return 0;
}
