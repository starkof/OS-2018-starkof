// Tests for hash table

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "concurrent_data_structures.h"

hash_t table;

void * thread_inserter(){
    for (int i = 0; i < 10000; ++i) {
        Hash_Insert(&table, i*10);
    }

    return NULL;
}

int main(int argc, char *argv[]){
    printf("Initializing hash table\n");

    Hash_Init(&table);

    printf("Adding 10 items to the hash table\n");

    for (int i = 0; i < 10; ++i) {
        Hash_Insert(&table, i);
    }

    printf("Expected length after insert = 10\n");
    printf("Length after insert: %d\n", Hash_Length(&table));

    printf("Inserting 10,000 items each in two threads\n\n");

    pthread_t p1, p2;

    pthread_create(&p1, NULL, thread_inserter, "A");
    pthread_create(&p2, NULL, thread_inserter, "B");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Expected length after insert = 20010\n");
    printf("Length after insert: %d\n", Hash_Length(&table));

    return 0;
}
