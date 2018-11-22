//
// Created by Stephan Ofosuhene on 11/22/18.
//

#ifndef PROJECT_4_CONCURRENT_H
#define PROJECT_4_CONCURRENT_H

typedef struct __counter_t{
    int value;
    pthread_mutex_t lock;
} counter_t;


void init(counter_t *c);


void increment(counter_t *c);


void decrement(counter_t *c);


int get_count_val(counter_t *c);


#endif //PROJECT_4_CONCURRENT_H
