#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#define N 100

typedef struct{
    char v[N];
    bool flag;
    pthread_mutex_t mutex;
    pthread_cond_t non_pieno;
    pthread_cond_t non_vuoto;
}TS;

void* produttore(void* arg){
    TS* s = (TS*) arg;
    while(1){
        if(pthread_mutex_lock(&s->mutex)!=0){
            printf("Errore lock mutex");
        }
        while(s->flag==true)
            pthread_cond_wait(&s->non_pieno, &s->mutex);
        printf("Inserire stringa: ");
        scanf("%s", s->v);
        s->flag=true;
        if(pthread_mutex_unlock(&s->mutex)!=0){
            printf("Errore unlock mutex");
        }
        pthread_cond_signal(&s->non_vuoto);
    }
    
}
int main(){
    TS s;
    int l;
    pthread_t tid;
    s.flag=false; //false: empty, true: full
    pthread_mutex_init(&s.mutex, NULL);
    pthread_cond_init(&s.non_pieno, NULL);
    pthread_cond_init(&s.non_vuoto, NULL);
    pthread_create(&tid, NULL, produttore, &s);
    while(1){
        if(pthread_mutex_lock(&s.mutex)!=0){
            printf("Errore lock mutex");
            return 1;
        }
        while(s.flag==false)
            pthread_cond_wait(&s.non_vuoto, &s.mutex);
        l=strlen(s.v);
        printf("Lunghezza stringa: %d\n", l);
        s.flag=false;
        if(pthread_mutex_unlock(&s.mutex)!=0){
            printf("Errore unlock mutex");
            return 1;
        }
        pthread_cond_signal(&s.non_pieno);
    }
}

