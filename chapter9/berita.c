#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char *feeds[]= {
        "https://en.antaranews.com/rss/news.xml",
        "https://www.sindonews.com/feed",
        "https://mediaindonesia.com/feed/all",
    };

    int times = 3;
    char *phrase = argv[1];
    int i;
    for (i = 0; i < times; i++) {
        char var[255];
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        pid_t pid = fork();
        if (pid == 1) {
            fprintf(stderr, "child process created\n", strerror(errno));
            return 1;
        }

        if (pid == 0) {
            if (execle("/usr/bin/python", "/usr/bin/python", "/home/learn/LearnC/HeadFirstC/chapter9/./rssgossip.py", phrase, NULL, vars) == - 1) {
                fprintf(stderr, "can't run script" , strerror(errno));
                return -1;
            }
        }else {
            int status;
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}
