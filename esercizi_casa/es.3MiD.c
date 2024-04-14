#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>

void ordina(float*v, int n){
    int i,k;    //è l'algoritmo di bubble sort!!!
    bool modified;
    modified = true;
    for(k=0; k<n-1 && modified; k++){
        modified=false;
        for(i=0; i<n-k-1; i++){
            if(v[i]>v[i+1]){
                float tmp=v[i];
                v[i]=v[i+1];
                v[i+1]=tmp;
                modified=true;
            }
        }
    }
}

int main(int argc, char* argv[]){
    int i;
    int n=atoi(argv[1]);
    int segment_id=shmget(IPC_PRIVATE, n*sizeof(float), S_IRUSR | S_IWUSR);
    if(segment_id==-1){
        printf("Errore nella creazione dell'area di mem condivisa");
        shmctl(segment_id, IPC_RMID, NULL);
        return 1;
    }
    pid_t pid = fork();
    if(pid<0){
        printf("Errore fork");
        shmctl(segment_id, IPC_RMID, NULL);
        return 1;
    }
    if(pid==0){
        float* v = (float*)shmat(segment_id, NULL, 0);
        for(i=0; i<n; i++){
            printf("Inserire il %do numero: ",i+1);
            scanf("%f",v+i);
        }
        ordina(v,n);
        shmdt(v);
    }
    if(pid>0){
        wait(NULL);
        int i;
        float* vet = (float*)shmat(segment_id, NULL, 0);
        for(i=0; i<n; i++){
            printf("%f ",vet[i]);
        }
        shmdt(vet);
        shmctl(segment_id, IPC_RMID, NULL);
    }
    return 0;
}

