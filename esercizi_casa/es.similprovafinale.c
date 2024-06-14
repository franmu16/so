#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int number;
    bool vuoto;/* true se il buffer e' vuoto*/
    pthread_mutex_t mutex;
    pthread_cond_t cond_var;
}TBuffer;

void *producer_thread(void *);
void *consumer_thread(void *);

double HarmonicNumber(int n){
    double harmonic_number = 0;
    for(int i=0; i < n; i++){
        if(i%2==0)
            harmonic_number += 1.0/(i+1);
        else
            harmonic_number -=1.0/(i+1);
    }
    return harmonic_number;
} 
int main (){
    pthread_t tid[2];
    TBuffer t;
    pthread_mutex_init(&t.mutex, NULL);
    pthread_cond_init(&t.cond_var, NULL);
    t.vuoto=true;
    t.number=1;
    if(pthread_create(&tid[1], NULL, producer_thread, &t)!=0){
        printf("Errore thread produttore");
        return 1;
    }
    if(pthread_create(&tid[0], NULL, consumer_thread, &t)!=0){
        printf("Errore thread consumatore");
        return 1;
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    return 0;
}

void* producer_thread(void* param){
    TBuffer* t = (TBuffer*) param;
    while(t->number>0){
        pthread_mutex_lock(&t->mutex);
        while(t->vuoto==false)
            pthread_cond_wait(&t->cond_var, &t->mutex);
        printf("Digitare numero: ");
        scanf("%d", &t->number);
        t->vuoto=false;
        pthread_mutex_unlock(&t->mutex);
        pthread_cond_signal(&t->cond_var);
    }
}

void* consumer_thread(void* param){
    TBuffer* t = (TBuffer*) param;
    double numero;
    while(true){
        pthread_mutex_lock(&t->mutex);
        while(t->vuoto==true)
            pthread_cond_wait(&t->cond_var, &t->mutex);
        if(t->number<0)
            return;
        numero=HarmonicNumber(t->number);
        printf("Numero armonico alternato di %d: %f\n", t->number, numero);
        t->vuoto=true;
        pthread_mutex_unlock(&t->mutex);
        pthread_cond_signal(&t->cond_var);
    }
}
