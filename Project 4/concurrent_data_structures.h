//
// Created by Stephan Ofosuhene on 11/22/18.
//

#ifndef PROJECT_4_CONCURRENT_H
#define PROJECT_4_CONCURRENT_H


// Counter
typedef struct __counter_t{
    int value;
    pthread_mutex_t lock;
} counter_t;


void init(counter_t *c);


void increment(counter_t *c);


void decrement(counter_t *c);


int get_count_val(counter_t *c);


// Linked List
typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L);

int List_Insert(list_t *L, int key);

int List_Lookup(list_t *L, int key);

int List_Length(list_t *L);

#endif //PROJECT_4_CONCURRENT_H
