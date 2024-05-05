#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int* v;
    int n;
    float res;
}TS;
void* massimo (void* arg){
    TS* vet = (TS*) arg;
    int max = vet->v[0];
    for(int i=1; i<vet->n; i++){
        if(max<vet->v[i])
            max=vet->v[i];
    }
    vet->res=max;
}
void* minimo (void* arg){
    TS* vet = (TS*) arg;
    int min = vet->v[0];
    for(int i=1; i<vet->n; i++){
        if(min>vet->v[i])
            min=vet->v[i];
    }
    vet->res=min;
}
void* media (void* arg){
    TS* vet = (TS*) arg;
    int i,sum=0;
    for(i=0; i<vet->n; i++){
        sum = sum + vet->v[i];
    }
    vet->res = sum/vet->n;
}
int main(){
    int n=1,i=0;
    int tmp;
    TS s1,s2,s3;
    //printf("Digitare quantità di numeri da analizzare: ");  //si può fare con do-while
    //scanf("%d", &n);
    int* v = (int*)malloc(1*sizeof(int));
    do{
        v[i]=tmp;
        i++;
        n++;
        if(i+1>n/2)
            v = (int*)realloc(v,n*2*sizeof(int));
        printf("Inserire numero (digitare  0 per terminare la lettura): ");
        scanf("%d",&tmp);
    }while(tmp!=0);
    s1.v=v; s2.v=v; s3.v=v;
    s1.n=n; s2.n=n; s3.n=n;
    pthread_t tid[3];
    pthread_create(&tid[1], NULL, massimo, &s1);
    pthread_create(&tid[2], NULL, minimo, &s2);
    pthread_create(&tid[3], NULL, media, &s3);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    printf("Massimo: %f\nMinimo: %f\nMedia: %f\n",s1.res,s2.res,s3.res);
    free(v);
    return 0;
}

