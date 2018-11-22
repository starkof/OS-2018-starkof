// Tests for concurrent queue

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "concurrent_data_structures.h"

// create concurrent queue
queue_t conc_queue;

void * thread_enqueue(){
    int k;
    for (int i = 0; i < 10000; ++i) {
        k = i*10;
        Queue_Enqueue(&conc_queue, k);
    }

    return NULL;
}

void * thread_dequeue(){
    int k;
    for (int i = 0; i < 10000; ++i) {
        k = i*10;
        Queue_Dequeue(&conc_queue, &k);
    }

    return NULL;
}

int main(int argc, char *argv[]){
    printf("Initializing concurrent queue\n");

    Queue_Init(&conc_queue);

    printf("Initial length: %d\n", Queue_Length(&conc_queue));

    printf("Adding 10 items to the queue\n");

    for (int i = 0; i < 10; ++i) {
        Queue_Enqueue(&conc_queue, i);
    }

    printf("Expected length after adding = 10\n");
    printf("Length after adding: %d\n", Queue_Length(&conc_queue));

    printf("Removing 5 items from the queue\n");

    for (int j = 0; j < 5; ++j) {
        Queue_Dequeue(&conc_queue, &j);
    }

    printf("Expected length after removing = 5\n");
    printf("Length after removing: %d\n\n", Queue_Length(&conc_queue));

    printf("Adding 10,000 items each in 2 threads\n");

    pthread_t p1, p2, p3, p4;
    pthread_create(&p1, NULL, thread_enqueue, "A");
    pthread_create(&p2, NULL, thread_enqueue, "B");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Expected length after enqueue = 20005\n");
    printf("Length after enqueue: %d\n\n", Queue_Length(&conc_queue));

    printf("Removing 10,000 items each in 2 threads\n");

    pthread_create(&p3, NULL, thread_dequeue, "C");
    pthread_create(&p4, NULL, thread_dequeue, "D");

    pthread_join(p3, NULL);
    pthread_join(p4, NULL);

    printf("Expected length after dequeue = 5\n");
    printf("Length after dequeue: %d\n", Queue_Length(&conc_queue));

    return 0;
}
