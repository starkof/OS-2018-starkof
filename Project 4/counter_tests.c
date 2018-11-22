// Tests for concurrent counter


#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include "concurrent_data_structures.h"

counter_t count;

void * thread_counter(){
    for (int i = 0; i < 10000; ++i) {
        increment(&count);
    }
    printf("Done multithreaded count");
    return NULL;
}

int main(int argc, char *argv[]){
    printf("Starting counter tests\n");

    init(&count);

    printf("Initial count value: %d\n", get_count_val(&count));

    for (int i = 0; i < 10; ++i) {
        increment(&count);
    }

    printf("Expected count = 10\n");
    printf("Counter value after incrementing 10 times: %d\n\n", get_count_val(&count));

    printf("Incrementing value by 10,000 each in 2 threads\n");

//    pid_t pid = fork();

    pthread_t p1, p2;

    pthread_create(&p1, NULL, thread_counter, "A");
    pthread_create(&p2, NULL, thread_counter, "B");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Expected count = 20010\n");
    printf("Counter value after multithreaded increment: %d\n\n", get_count_val(&count));

    return 0;
}
