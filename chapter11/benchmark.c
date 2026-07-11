#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>

#define NUM_TASKS 1000
#define WORKLOAD 100000000

// Function to simulate work
void do_work() {
    volatile long sum = 0;
    for (int i = 0; i < WORKLOAD; i++) {
        sum += i;
    }
}

// Function for pthread
void *thread_work(void *arg) {
    do_work();
    return NULL;
}

// Helper to get time in milliseconds
double get_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000.0) + (ts.tv_nsec / 1000000.0);
}

int main() {
    double start, end;


    // --- 2. MULTI-PROCESS (Using fork) ---
    start = get_time_ms();
    for (int i = 0; i < NUM_TASKS; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Child
            do_work();
            exit(0);
        }
    }
    // Wait for all children to finish
    for (int i = 0; i < NUM_TASKS; i++) {
        wait(NULL);
    }
    end = get_time_ms();
    printf("Fork (Child) Time: %.2f ms\n", end - start);

    // --- 3. MULTI-THREADED (Using pthread.h) ---
    start = get_time_ms();
    pthread_t threads[NUM_TASKS];
    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_create(&threads[i], NULL, thread_work, NULL);
    }
    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_join(threads[i], NULL);
    }
    end = get_time_ms();
    printf("Pthread Time: %.2f ms\n", end - start);

    return 0;
}
