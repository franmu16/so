//ESERCIZIO LA CUI TRACCIA E' STATA FORNITA DA COPILOT E LEGGERMENTE MODIFICATA -> NON E' UN PROGRAMMA "LOGICO" MA FUNZIONA
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DIM 10
#define PRODUCER_SLEEP_SEC 1
#define CONSUMER_SLEEP_SEC 2
#define MAIN_SLEEP_SEC 120

// Definizione della struttura del buffer
typedef struct {
    int buffer[DIM];
    int count;
    int in;
    int out;
    pthread_mutex_t mutex;
    pthread_cond_t notEmpty;
    pthread_cond_t notFull;
} TBuffer;

void *producer(void *arg){
    TBuffer* t = (TBuffer*) arg;
    while(1){
        pthread_mutex_lock(&t->mutex);
        while(t->count>=DIM)
            pthread_cond_wait(&t->notFull, &t->mutex);
	sleep(PRODUCER_SLEEP_SEC);
        printf("Inserire valore: ");
        scanf("%d", &t->buffer[t->out]);
        t->out=(t->out+1)%DIM;
        t->count=t->count+1;
        pthread_mutex_unlock(&t->mutex);
        pthread_cond_broadcast(&t->notEmpty);
    }
    
}

void *consumer(void *arg){
    TBuffer* t = (TBuffer*) arg;
    while(1){
        pthread_mutex_lock(&t->mutex);
        while(t->count<=0)
            pthread_cond_wait(&t->notEmpty, &t->mutex);
	sleep(CONSUMER_SLEEP_SEC);
        printf("Valore: %d\n", t->buffer[t->in]);
        t->in=(t->in+1)%DIM;
        t->count=t->count-1;
        pthread_mutex_unlock(&t->mutex);
        pthread_cond_broadcast(&t->notFull);
    }
}

int main () {
    TBuffer t;
    pthread_t tid[3];
    t.count=0;
    t.in=0;
    t.out=0;
    pthread_mutex_init(&t.mutex,NULL);
    pthread_cond_init(&t.notFull,NULL);
    pthread_cond_init(&t.notEmpty,NULL);
    if(pthread_create(&tid[0], NULL, producer, &t)!=0){
        printf("Errore produttore1");
        return 1;
    }
    if(pthread_create(&tid[1], NULL, producer, &t)!=0){
        printf("Errore produttore2");
        return 1;
    }
    if(pthread_create(&tid[2], NULL, consumer, &t)!=0){
        printf("Errore consumer");
        return 1;
    }
    sleep(MAIN_SLEEP_SEC);
    return 0;
}
