#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    struct timeval end;
    //gettimeofday(&begin, NULL);
    int segment_id=shmget(IPC_PRIVATE, sizeof(struct timeval), S_IRUSR | S_IWUSR);
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
        char c[]="/bin/";
        struct timeval *p=(struct timeval *)shmat(segment_id, NULL, 0);
        gettimeofday(p, NULL);
        strcat(c,argv[1]);
        execlp(c,argv[1],NULL);
        
        // Detach shared memory
        shmdt(p);
        return 0;
    } else {
        wait(NULL);
        // Attach shared memory
        struct timeval *v = (struct timeval *)shmat(segment_id, NULL, 0);
        //gettimeofday(&end, NULL);
        gettimeofday(&end, NULL);
        double durata = (end.tv_sec - v->tv_sec) + ((end.tv_usec - v->tv_usec) / 1000000.0);
        printf("Durata esecuzione in millisecondi: %f", durata);
        // Detach shared memory
        shmdt(v);
        // Important! Shared Memory deallocation
        shmctl(segment_id, IPC_RMID, NULL);
        return 0;
    }
}

