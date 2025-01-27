#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

long double globalSum = 0.0;
pthread_mutex_t mutexLock;
long numTerm, numThread;

void *computePartialPI(void *arg){
    long threadId = *(long*)arg;

    long start = (numTerm / numThread) * threadId + 1;
    long end = (numTerm / numThread) * (threadId + 1);
    long double localSum = 0.0;

    for (long i = start; i <= end; i++){
        long double x = ((long double)i - 0.5) / numTerm;
        localSum += 4.0 / (1.0 + x * x);
    }

    pthread_mutex_lock(&mutexLock);
    globalSum += localSum;
    pthread_mutex_unlock(&mutexLock);

    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number of threads> <number of terms>\n", argv[0]);
        return 0;
    }

    numThread = strtol(argv[1], NULL, 10);
    numTerm = strtol(argv[2], NULL, 10);

    if (numThread <= 0 || numTerm <= 0) {
        fprintf(stderr, "Error: Both number of threads and terms must be positive integers.\n");
        return 0;
    }

    pthread_t threads[numThread];
    long threadIds[numThread];
    pthread_mutex_init(&mutexLock, NULL);

    for (long i = 0; i < numThread; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, computePartialPI, &threadIds[i]);
    }

    for (long i = 0; i < numThread; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutexLock);

    long double PIEstimate = globalSum / numTerm;
    long double PI = 3.141592653589793238462643383279502884197L;
    long double error = fabsl(PIEstimate - PI);

    printf("pi is approx %.22Lf\n", PIEstimate);
    printf("actual value of pi is %.22Lf\n", PI);
    printf("the error is %.22Lf\n", error);

    return 1;
}
