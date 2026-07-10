#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void open_url(char *url) {
    pid_t pid = fork();
    if (pid == -1) {
        error("can't fork");
    }
    if (pid == 0) {
        if (execlp("/usr/bin/xdg-open", "/usr/bin/xdg-open", url,NULL) == -1) {
            error("can't run script");
        }
    }else {
        int status;
        waitpid(pid, &status, 0);
        printf("status succes");
    }
}

int main(int argc, char *argv[]) {
    char *feeds[]= {
        "https://en.antaranews.com/rss/news.xml",
        "https://www.sindonews.com/feed",
        "https://mediaindonesia.com/feed/all",
    };

    int times = 3;
    char *phrase = argv[1];
    int i;
    FILE *f = fopen("output.txt", "w");


    for (i = 0; i < times; i++) {
        char var[255];
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        pid_t pid = fork();
        if (pid == 1) {
            fprintf(stderr, "child process created\n", strerror(errno));
            return 1;
        }

        //change the file descriptor
        if (pid == 0) {
            if (dup2(fileno(f), 1)  == -1) {
                error("cant replace file descriptor");
            }

            if (execle("/usr/bin/python", "/usr/bin/python", "/home/learn/LearnC/HeadFirstC/chapter9/./rssgossip.py", "-u",phrase, NULL, vars) == - 1) {
                fprintf(stderr, "can't run script" , strerror(errno));
                return -1;
            }
        }else {
            int pid_status;
            waitpid(pid, &pid_status, 0);

            // 1. Verify the child terminated normally
            if (WIFEXITED(pid_status)) {
                // 2. Extract the actual exit status
                int exit_code = WEXITSTATUS(pid_status);
                printf("Child exited normally with code: %d\n", exit_code);
            } else {
                printf("Child did not terminate normally.\n");
            }
        }
    }
    return 0;
}
