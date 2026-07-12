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
    url[strcspn(url, "\r\n\t")] = 0;

    if (strlen(url) == 0) return;

    pid_t pid = fork();
    if (pid == -1) {
        error("can't fork");
    }
    if (pid == 0) {
        if (// Untuk tes kebersihan string URL di terminal jika masih error:
        execlp("xdg-open","xdg-open", url,NULL) == -1) {
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
        "https://www.viva.co.id/get/all",
        "https://www.jpnn.com/index.php?mib=rss",
    };


    int time = 5;
    for (int i = 0; i < time; i++) {

        char var[255];
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        char *phrase = argv[1];
        int fd[2];
        if (pipe(fd) == -1) {
            error("can't open pipe");
        }

        pid_t pid = fork();
        if (pid == -1) {
            error("can't fork");
        }
        if (pid == 0) {
            dup2(fd[1], 1);
            close(fd[0]);


            if (execle("/usr/bin/python", "/usr/bin/python", "/home/learn/LearnC/HeadFirstC/chapter9/rssgossip.py", "-u",phrase, NULL, vars) == -1) {
                error("can't run script");
            }
        }

        // dup2(fd[0], 0);
        close(fd[1]);

        FILE *pipe_stream = fdopen(fd[0], "r");
        if (pipe_stream == NULL) {
            error("can't open pipe stream");
        }

        char line[255];
        while (fgets(line, 255, pipe_stream) != NULL) {
            char *url_start = strstr(line, "http");
            if (url_start != NULL) {
                open_url(url_start);
            } else {
                printf("judul: %s", line);;
            }
        }
        fclose(pipe_stream);

        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
}