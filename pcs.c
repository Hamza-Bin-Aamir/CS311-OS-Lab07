#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_THREADS 6

void* runner(void* arg) {
    sleep(1);
    printf("Hello from thread %ld\n", (long)arg);
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int i, scope;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    if(pthread_attr_getscope(&attr, &scope) != 0) {
        fprintf(stderr, "Unable to get scheduling scope\n");
        return 1;
    }
    
    if(scope == PTHREAD_SCOPE_SYSTEM)
        printf("PTHREAD SCOPE SYSTEM\n");
    else if(scope == PTHREAD_SCOPE_PROCESS)
        printf("PTHREAD SCOPE PROCESS\n");
    else
        printf("Illegal scope value\n");

    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    for(i = 0; i < NUM_THREADS; i++) {
        int rc = pthread_create(&tid[i], &attr, runner, (void*)(long)i);
        if (rc != 0) {
            fprintf(stderr, "pthread_create failed: %d\n", rc);
            return 1;
        }
    }

    for(i=0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    return 0;
}