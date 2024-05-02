#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
  int n;
  int r;
}TS;

int factorial (int n){
  if(n==0 || n==1)
    return 1;
  return factorial(n-1)*n;
}
void *factorial_thread(void *arg){
    TS* str = (TS*) arg;
    str->r=factorial(str->n);
}
int main(int argc, char* argv[]){
    int i;
    TS t[3];
    do{
    printf("Digitare n:");
    scanf("%d",&t[0].n);
    }while(t[0].n<=0);
    do{
    printf("Digitare k:");
    scanf("%d",&t[1].n);
    }while(t[1].n<=0 || t[1].n>t[0].n);
    t[2].n = t[0].n-t[1].n;
    pthread_t thread_id[3];
    for(i=0; i<3; i++){
        if(pthread_create(&thread_id[i], NULL, factorial_thread , t+i)!=0){
            printf("Errore in creazione del %do thread", i+1);
            return 0;
        }
    }
    for(i=0; i<3; i++)
        pthread_join(thread_id[i], NULL);
    printf("n!: %d,  k!: %d, (n-k)!: %d\n",t[0].r, t[1].r, t[2].r);
    float c = (float)t[0].r/(t[1].r*t[2].r);
    printf("Coefficiente binomiale: %f", c);
    return 0;
}

