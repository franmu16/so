#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#define N 10

typedef struct{
    char str[100];
    bool flag; //true=full, false=empty
    pthread_cond_t cond;
    pthread_mutex_t mutex;
}TParam;
typedef struct {
    int id;
    TParam *s;
}TBuffer;

void* consumer(void* arg){
    TBuffer* b=(TBuffer*) arg;
    TParam* t=b->s;
    while(1){
        pthread_mutex_lock(&t->mutex);
        while(t->flag==false)
            pthread_cond_wait(&t->cond, &t->mutex);
        printf("ID: %d, stringa: %s\n", b->id, t->str);
        t->flag=false;
        sleep(2);
        pthread_cond_broadcast(&t->cond);
        pthread_mutex_unlock(&t->mutex);
    }
    return NULL;
}

void* producer(void* arg){
    TBuffer* b=(TBuffer*) arg;
    TParam* t=b->s;
    while(1){
	    pthread_mutex_lock(&t->mutex);
        while(t->flag==true)
            pthread_cond_wait(&t->cond, &t->mutex);
        printf("Inserire stringa (dim. max 100 caratteri): ");
        scanf("%s", t->str);
        t->flag=true;
        pthread_cond_signal(&t->cond);
        pthread_mutex_unlock(&t->mutex);
    }
    return NULL;
}

int main(){
    pthread_t tid[N+1];
    TBuffer p[N+1];
    TParam b;
    int i;
    b.flag=false;
    pthread_cond_init(&b.cond, NULL);;
    pthread_mutex_init(&b.mutex, NULL);
    p[0].id = 0;
    p[0].s = &b;
    pthread_create(&tid[0], NULL, producer, &p[0]);
    for(i = 1; i <= N; i++){
        p[i].id = i;
        p[i].s = &b;
        pthread_create(&tid[i], NULL, consumer, &p[i]);
    }
    for(i=0; i<=N; i++)
        pthread_join(tid[i], NULL);
}

