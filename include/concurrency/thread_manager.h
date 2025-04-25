#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

// Thread structure to pass data to thread routines
typedef struct {
    int thread_id;
    void* (*task)(void*);
    void* args;

} ThreadTask;

// initializes and starts a thread
int start_thread(pthread_t *thread, void *(*task)(void *), void *args);

// Joins the specified thread
int join_thread(pthread_t thread);

// Creates and runs multiple threads
int run_multiple_threads(ThreadTask *tasks, int count);


#endif // THREAD_MANAGER_H