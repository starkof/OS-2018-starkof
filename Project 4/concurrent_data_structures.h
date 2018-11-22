//
// Created by Stephan Ofosuhene on 11/22/18.
//

#ifndef PROJECT_4_CONCURRENT_H
#define PROJECT_4_CONCURRENT_H

#define BUCKETS (101)


// Counter ============================================================
typedef struct __counter_t{
    int value;
    pthread_mutex_t lock;
} counter_t;


void init(counter_t *c);


void increment(counter_t *c);


void decrement(counter_t *c);


int get_count_val(counter_t *c);


// Linked List ============================================================
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


// Queue ============================================================
typedef struct __qnode_t {
    int value;
    struct __qnode_t *next;
} qnode_t;

typedef struct __queue_t {
    qnode_t *head;
    qnode_t *tail;
    pthread_mutex_t headLock;
    pthread_mutex_t tailLock;
} queue_t;

void Queue_Init(queue_t *q);

void Queue_Enqueue(queue_t *q, int value);

int Queue_Dequeue(queue_t *q, int *value);

int Queue_Length(queue_t *q);


// Hash Table ============================================================
typedef struct __hash_t {
    int length;
    list_t lists[BUCKETS];
} hash_t;

void Hash_Init(hash_t *H);

int Hash_Insert(hash_t *H, int key);

int Hash_Lookup(hash_t *t, int key);

int Hash_Length(hash_t *H);

#endif //PROJECT_4_CONCURRENT_H
