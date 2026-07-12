#include <pthread.h>
#include <stdio.h>
#include <bits/pthreadtypes.h>
#include <stdlib.h>
int beers = 2000000;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *drink_lots(void *a) {
    int i;
    long id = (long)a;
    for (i = 0; i < 100000; i++) {
        // Performs an atomic thread-safe subtraction
        pthread_mutex_lock(&mutex);
        beers = beers - 1;
        pthread_mutex_unlock(&mutex);
    }
    printf("%i bottles of beer on the wall and id == %i\n", beers,id);

    return NULL;
}


int main(int argc, char *argv[]) {
    pthread_t thread[20];
    long t;
    printf("%i bootles of beer on the wall\n%i bottles of beer\n", beers, beers);
    for (t = 0; t < 20; t++) {
        pthread_create(&thread[t], NULL, drink_lots, (void *)t);
        }

    void *result;
    for (t = 0; t < 20; t++) {
        pthread_join(thread[t],&result);
    }
    printf("%i bottles of beer on the wall\n", beers);
    return 0;

    }

