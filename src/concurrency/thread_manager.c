#include "../../include/concurrency/thread_manager.h"
#include <stdio.h>
#include <stdlib.h>

int start_thread(pthread_t *thread, void *(*task)(void*), void *args) {
    if (pthread_create(thread, NULL, task, args) != 0) {
        perror("Failed to create thread");
        return -1;

    }
    return 0;
}


int run_multiple_threads(ThreadTask *tasks, int count) {
    pthread_t *threads = malloc(sizeof(pthread_t) * count);
    if(!threads) {
      perror("Memory allocation failed");
      return -1;
    }

    for(int i = 0; i < count; i++) {
        if (start_thread(&threads[i], tasks[i].task, tasks[i].args) !=0) {
            free(threads);

            return -1;
        }
    }

    for (int i = 0; i < count; i++) {
        if (join_thread(threads[i]) !=0) {
            free(threads);

            return -1;
        }
    }

    free(threads);
    return 0;
}
 
int join_thread(pthread_t thread) {
    if (pthread_join(thread, NULL) != 0) {
        perror("Failed to join thread");
        return -1;
    }
    return 0;
}