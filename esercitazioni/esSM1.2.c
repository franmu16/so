#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>

void child_process(int,int);
int main() {
    int max= 100*sizeof(float);
    int segment_id=shmget(IPC_PRIVATE, max, S_IRUSR | S_IWUSR);
    if (segment_id<0) {
        printf("shmget error\n");
        return 1;
    }

    pid_t pid=fork();
    if (pid<0) {
        fprintf(stderr, "fork error\n");
        // Important! Shared Memory deallocation
        shmctl(segment_id, IPC_RMID, NULL);
        return 1;
    } else if (pid==0) {
        pid_t pid2=fork();
        if (pid2<0) {
        fprintf(stderr, "fork error\n");
        // Important! Shared Memory deallocation
        shmctl(segment_id, IPC_RMID, NULL);
        return 1;
        }
        if(pid2==0){
          child_process(segment_id,51);  
        }
        else{
          wait(NULL);
          child_process(segment_id,1);
        }
        // Detach shared memory

        return 0;
    } else {
        // Father process
        // Wait for child before accessing to shared memory
        wait(NULL);
        // Attach shared memory
        float *v = (float *)shmat(segment_id, NULL, 0);
        float somma=0;
        for(int i=0; i<100; i++)
          somma=somma+v[i];
        printf("Somma valori: %f\n", somma);
        // Detach shared memory
        shmdt(v);
        // Important! Shared Memory deallocation
        shmctl(segment_id, IPC_RMID, NULL);
        return 0;
    }
}

void child_process(int segment_id, int start){
    float *p=(float *)shmat(segment_id, NULL, 0); 
    for(int i=start; i<start+50; i++){
       p[i]=(float)(1)/(float)(i);
    }
    shmdt(p);
}
