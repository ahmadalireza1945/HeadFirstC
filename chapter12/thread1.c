#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>

void* does_not(void* a) {
    int i = 0;
    for (; i < 5; i++) {
        sleep(1);
        puts("Does Not!");
    }

    return NULL;
}

void* does_too(void* a) {
    int i = 0;
    for (; i < 5; i++) {
        sleep(1);
        puts("Does too!");
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t th0;
    pthread_t th1;
    if (pthread_create(&th0,NULL,does_not,NULL) == -1) {
        fprintf(stderr,"pthread_create() failed");
    }
    if (pthread_create(&th1,NULL,does_too,NULL) == -1) {
        fprintf(stderr,"pthread_create() failed");
    }

    void* result;
    if (pthread_join(th0,&result) == -1) {
        fprintf(stderr,"pthread_join() failed");
    }
    if (pthread_join(th1,&result) == -1) {
        fprintf(stderr,"pthread_join() failed");
    }
}

