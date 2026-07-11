#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    // 1. Create exactly 3 child processes
    for (int i = 0; i < 5; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // This block is executed by the CHILD process
            printf("Child %d created: PID = %ld, Parent PID = %ld\n",
                   i + 1, (long)getpid(), (long)getppid());
            _exit(0); // Child exits to avoid continuing the parent's loop
        }
    }

    // 2. Parent waits for all 3 child processes to finish
    for (int i = 0; i < 5; i++) {
        int status;
        pid_t terminated_pid = wait(&status);
        if (terminated_pid > 0) {
            printf("Parent reaped child with PID = %ld\n", (long)terminated_pid);
        }
    }

    printf("All children completed. Parent process terminating.\n");
    return EXIT_SUCCESS;
}
