#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *indice(void *arg){
    int* n = (int*) arg;
    printf("Thread %d: %d\n",*n, *n);
}
int main(int argc, char* argv[]){
    int i;
    if(argc < 2){
        printf("No number");
        return 0;
    }
    int N = atoi(argv[1]);
    int* v = malloc(N*sizeof(int));
    for(i=0; i<N; i++)
        v[i]=i;
    pthread_t thread_id[N];
    for(i=0; i<N; i++){
        if(pthread_create(&thread_id[i], NULL, indice , v+i)!=0){
            printf("Errore in creazione del %do thread", i+1);
            return 0;
        }
    }
    for(i=0; i<N; i++)
        pthread_join(thread_id[i], NULL);
    free(v);
    return 0;
}

