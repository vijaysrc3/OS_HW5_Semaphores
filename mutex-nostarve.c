#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {
sem_t lock;
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m) {
sem_init(&m->lock, 0, 1);
}

void ns_mutex_acquire(ns_mutex_t *m) {
sem_wait(&m->lock);
}

void ns_mutex_release(ns_mutex_t *m) {
sem_post(&m->lock);
}

ns_mutex_t n;
int c=0;
void *worker(void *arg) {
    ns_mutex_acquire(&n);
    c++;
    ns_mutex_release(&n);
    return NULL;
}

int main(int argc, char *argv[]) {
  assert(argc==2);
    int thread_number = atoi(argv[1]);
    pthread_t p[thread_number];
    ns_mutex_init(&n);
    
    printf("parent: begin\n");
    int i;
    for(i=0;i<thread_number;i++)
    {
    pthread_create(&p[i],NULL,worker,NULL);
    }
    
    int j;
    for(j=0;j<thread_number;j++)
    {
    pthread_join(p[j],NULL);
    }
    printf("Counter value : %d \n",c);
    printf("parent: end\n");
    return 0;
}

