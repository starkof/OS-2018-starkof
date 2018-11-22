// concurrent data structures


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

#define BUCKETS (101)

// counter ============================================================
typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}

int get_count_val(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);

    return rc;
}


// linked list ============================================================
typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

typedef struct __list_t {
    int length;
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L) {
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(list_t *L, int key) {
    pthread_mutex_lock(&L->lock);
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("malloc");
        pthread_mutex_unlock(&L->lock);
        return -1; // fail
    }

    new_node->key  = key;
    new_node->next = L->head;
    L->head   = new_node;

    L->length++;
    pthread_mutex_unlock(&L->lock);

    return 0; // success
}

int List_Lookup(list_t *L, int key){
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            pthread_mutex_unlock(&L->lock);
            return 0; // success
        }
        curr = curr->next;pthread_mutex_unlock(&L->lock);
        return -1; // failure
    }

    return 0;
}

int List_Length(list_t *L){
    pthread_mutex_lock(&L->lock);
    int len = L->length;
    pthread_mutex_unlock(&L->lock);

    return len;

}

// queue ============================================================
typedef struct __qnode_t {
    int value;
    struct __qnode_t *next;
} qnode_t;

typedef struct __queue_t {
    int length;
    qnode_t *head;
    qnode_t *tail;
    pthread_mutex_t headLock;
    pthread_mutex_t tailLock;
} queue_t;

void Queue_Init(queue_t *q) {
    qnode_t *tmp = malloc(sizeof(qnode_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;
    pthread_mutex_init(&q->headLock, NULL);
    pthread_mutex_init(&q->tailLock, NULL);
}

void Queue_Enqueue(queue_t *q, int value) {
    qnode_t *tmp = malloc(sizeof(qnode_t));
    assert(tmp != NULL);
    tmp->value = value;
    tmp->next  = NULL;

    pthread_mutex_lock(&q->tailLock);
    q->tail->next = tmp;
    q->tail = tmp;

    q->length++;
    pthread_mutex_unlock(&q->tailLock);
}

int Queue_Dequeue(queue_t *q, int *value) {
    pthread_mutex_lock(&q->headLock);
    qnode_t *tmp = q->head;
    qnode_t *newHead = tmp->next;

    if (newHead == NULL) {
        pthread_mutex_unlock(&q->headLock);
        return -1; // queue was empty
    }

    *value = newHead->value;
    q->head = newHead;
    pthread_mutex_unlock(&q->headLock);
    free(tmp);

    q->length--;

    return 0;
}

int Queue_Length(queue_t *q) {
    pthread_mutex_lock(&q->headLock);
    pthread_mutex_lock(&q->tailLock);
    int len = q->length;
    pthread_mutex_unlock(&q->headLock);
    pthread_mutex_unlock(&q->tailLock);
    return len;
}

// hash table ============================================================
typedef struct __hash_t {
    int length;
    list_t lists[BUCKETS];
    pthread_mutex_t lengthlock;
} hash_t;

void Hash_Init(hash_t *H) {
    int i;
    for (i=0;i<BUCKETS;i++){
        List_Init(&H->lists[i]);
    }
}

int Hash_Insert(hash_t *H, int key) {
    pthread_mutex_lock(&H->lengthlock);
    int bucket = key % BUCKETS;
    H->length++;
    pthread_mutex_unlock(&H->lengthlock);
    return List_Insert(&H->lists[bucket], key);
}

int Hash_Lookup(hash_t *H, int key) {
    int bucket = key % BUCKETS;
    return List_Lookup(&H->lists[bucket], key);
}

int Hash_Length(hash_t *H) {
    pthread_mutex_lock(&H->lengthlock);
    int len = H->length;
    pthread_mutex_unlock(&H->lengthlock);
    return len;
}
