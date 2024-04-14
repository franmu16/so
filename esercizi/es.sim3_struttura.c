#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#define SIZE 10

typedef struct {
    char str[SIZE];
}shared_data;

int main(int argc, char* argv[]){
    int len = strlen(argv[1]);
    int segment_id = shmget(IPC_PRIVATE, sizeof(shared_data), S_IRUSR | S_IWUSR);
    if(segment_id==-1){
        printf("Errore creazione mem condivisa");
        shmctl(segment_id, IPC_RMID, NULL);
        return 1;
    }
    char*string;
    strncpy(string, argv[1],SIZE);
    pid_t pid = fork();
    if(pid<0){
        printf("Errore fork");
        shmctl(segment_id, IPC_RMID, NULL);
        return 1;
    }
    if(pid==0){
        int i; 
        shared_data* v= (shared_data*)shmat(segment_id, NULL, 0);
        strncpy(v->str,argv[1],SIZE);
        
        pid_t pid2=fork();
        if(pid2<0){
            printf("Errore fork");
            shmctl(segment_id, IPC_RMID, NULL);
            return 1;
        }
        if(pid2==0){
           for(i=0; i<len/2; i++){
                char tmp = v->str[i];
                v->str[i]=v->str[len-i-1];
                v->str[len-i-1]=tmp;
            } 
            shmdt(v);
        }
        else if(pid2>0){
            wait(NULL);
            shared_data*rev=(shared_data*)shmat(segment_id, NULL, 0);
            printf("Stringa originale: %s\n",string);
            printf("Stringa invertita: %s\n",rev->str);
            if(strcmp(rev->str,string)==0)
                printf("Stringa palindroma");
            else
                printf("Stringa non palindroma");
            shmdt(rev);
        }
        
    }
    if(pid>0){
        wait(NULL);
        shared_data* vet = (shared_data*)shmat(segment_id, NULL, 0);
        //printf("%s",vet);    //stampa dell'es.1
        shmdt(vet);
        shmctl(segment_id, IPC_RMID, NULL);
    }
    return 0;
}

