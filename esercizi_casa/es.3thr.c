#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define NTHREADS 4

typedef struct{
    int* v;
    int s;
}TS;
int fibonacci (int n){
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    else
        return fibonacci(n-1)+fibonacci(n-2);
}
void* fib (void* arg){
    TS* t = (TS*) arg;
    int i;
    for(i=0; i<t->s; i++){
        t->v[i] = fibonacci(t->v[i]);
    }
}
int main(int argc, char* argv[]){
    int i=0, n=1,tmp,j;
    TS s[NTHREADS];
    int flag=0;
    pthread_t tid[NTHREADS];
    int* v = (int*)malloc(10*sizeof(int));
    printf("Inserire numero (digitare numero negativo per terminare la lettura): ");
    scanf("%d",&tmp);
    while(tmp>=0){
        v[i]=tmp;
        i++;
        if(i+1>n/2){
            n=n*2;
            v = (int*)realloc(v,n*sizeof(int));
        }
        printf("Inserire numero (digitare numero negativo per terminare la lettura): ");
        scanf("%d",&tmp);
    }
    int size = (i+1)/NTHREADS;   //length vettore da passare al thread
    if(i!=size*NTHREADS)
       flag=1;
    for(j=0; j<NTHREADS; j++){
        if(flag==0){
            s[j].v=v+(j*size);
            s[j].s=size;
            if(pthread_create(&(tid[j]), NULL, fib, s+j)!=0){
                printf("Errore in creazione del thread");
                return 2;
            }
        }
        else{
            s[j].v=v+(j*size);
            if(j+1<NTHREADS)
                s[j].s=size;
            else
                s[j].s=(i*sizeof(int)-j*sizeof(int))/sizeof(int);
            if(pthread_create(&(tid[j]), NULL, fib, &s[j])!=0){
                printf("Errore in creazione del thread");
                return 2;
            }
        }
    }
    for(j=0; j<NTHREADS; j++){
        pthread_join(tid[j], NULL);
        int* tmp = s[j].v;
        for(i=0; i<s[j].s; i++)
            printf("%d ", tmp[i]);
    }
    return 0;
}

