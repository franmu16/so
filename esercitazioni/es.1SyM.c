#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define THREADS 2
#define START1 1
#define END1 50
#define START2 51
#define END2 100

typedef struct{
  int start;
  int end;
  int* psomma;
  pthread_mutex_t *mutex;
}TParam;

void *calcola_somma(void *arg){
  TParam* s = (TParam*) arg;
  int i;
  int somma = 0;
  for(i=s->start; i<=s->end; i++){
    somma = somma + i;
  }
  if(pthread_mutex_lock(s->mutex)!=0){
    printf("Errore");
    return 0;
  }
  *(s->psomma) = *(s->psomma) + somma;
  if(pthread_mutex_unlock(s->mutex)!=0){
    printf("Errore");
    return 0;
  }
}
int main(int argc, char *argv[]) {
  TParam str1, str2;
  int i;
  int somma = 0;
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);
  pthread_t tid[THREADS];
  for(i=0; i<THREADS; i++){
    if(i==0){
      str1.start = START1;
      str1.end = END1;
      str1.psomma = &somma;
      str1.mutex = &mutex;
      pthread_create(&tid[i], NULL, calcola_somma, &str1);
    }
     if(i==1){
      str2.start = START2;
      str2.end = END2;
      str2.psomma = &somma;
      str2.mutex = &mutex;
      pthread_create(&tid[i], NULL, calcola_somma, &str2);
     }
    if(tid[i]<0){
      printf("Errore thread");
    return 0;
    }
}
 pthread_join(tid[0], NULL);
 pthread_join(tid[1], NULL);
 printf("Somma: %d\n", somma);
 return 0;
}
