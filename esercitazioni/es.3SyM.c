#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
typedef struct{
    int conteggio;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}TS;

void* aggiungi(void* arg){
    TS* s = (TS*) arg;
    while(1){
        pthread_mutex_lock(&s->mutex);
        s->conteggio = s->conteggio + 1;
        pthread_cond_signal(&s->cond);
        printf("Conteggio incrementato: %d\n", s->conteggio);
        pthread_mutex_unlock(&s->mutex);
        sleep(1.2);  //l'ho velocizzato un po'!!!
    }
    return NULL;
}
void* azzera(void* arg){
    TS* s = (TS*) arg;
    while(1){
        pthread_mutex_lock(&s->mutex);
        while(s->conteggio!=10)
            pthread_cond_wait(&s->cond, &s->mutex);
        s->conteggio = 0;
        printf("Conteggio azzerato: %d\n", s->conteggio);
        pthread_mutex_unlock(&s->mutex);
    }
    return NULL;
}
int main(){
    TS s;
    pthread_t tid[2];
    s.conteggio=0;
    pthread_mutex_init(&s.mutex,NULL);
    pthread_cond_init(&s.cond,NULL);
    if(pthread_create(&tid[0], NULL, aggiungi, &s)!=0){
        printf("Errore thread");
        return 1;
    }
    if(pthread_create(&tid[1], NULL, azzera, &s)!=0){
        printf("Errore thread");
        return 1;
    }
    for(int i=0; i<2; i++){
        pthread_join(tid[i], NULL);
    }
    return 0;
}


/*
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
typedef struct{
    int conteggio;
    pthread_mutex_t* mutex;
    pthread_cond_t* cond;
}TS;

void* aggiungi(void* arg){
    TS* s = (TS*) arg;
    while(1){
        pthread_mutex_lock(s->mutex);
        s->conteggio = s->conteggio + 1;
        pthread_cond_signal(s->cond);
        printf("Conteggio incrementato: %d\n", s->conteggio);
        pthread_mutex_unlock(s->mutex);
        sleep(3);
    }
    return NULL;
}
void* azzera(void* arg){
    TS* s = (TS*) arg;
    while(1){
        pthread_mutex_lock(s->mutex);
        while(s->conteggio!=10)
            pthread_cond_wait(s->cond, s->mutex);
        s->conteggio = 0;
        printf("Conteggio azzerato: %d\n", s->conteggio);
        pthread_mutex_unlock(s->mutex);
    }
    return NULL;
}
int main(){
    TS s;
    pthread_t tid[2];
    s.conteggio=0;
    pthread_mutex_init(s.mutex,NULL);
    pthread_cond_init(s.cond,NULL);
    if(pthread_create(&tid[0], NULL, aggiungi, &s)!=0){
        printf("Errore thread");
        return 1;
    }
    if(pthread_create(&tid[1], NULL, azzera, &s)!=0){
        printf("Errore thread");
        return 1;
    }
    for(int i=0; i<2; i++){
        pthread_join(tid[i], NULL);
    }
    return 0;
}
*/
