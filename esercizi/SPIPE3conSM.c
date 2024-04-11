#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define N 100
struct crd{
  float x;
  float y;
  float z;
};
typedef struct crd cord;
int main(int argc, char* argv[]) {
    int i;
    cord message[50];
    int segment_id=shmget(IPC_PRIVATE, sizeof(message), S_IRUSR | S_IWUSR);

    if (segment_id < 0) {
        printf("Pipe creation error\n");
        shmctl(segment_id, IPC_RMID, NULL);
        return 1;
    }
    pid_t pid = fork();
    if (pid<0) {
        printf("fork error\n");
        shmctl(segment_id, IPC_RMID, NULL);
        return 1;
    } else if (pid == 0) {
        // Child process
        wait(NULL);
        cord* mes=(cord*)shmat(segment_id, NULL,0);
        for(i=0; i<50; i++){
            printf("%f %f %f", mes[i].x, mes[i].y, mes[i].z);
                 printf("\n");
        }
        shmdt(mes);
        shmctl(segment_id, IPC_RMID, NULL);
        return 0;
    } else {
        // Father process
        cord* mes=(cord*)shmat(segment_id, NULL,0);
        // Compose message
        for(i=0; i<50; i++){
          mes[i].x=i; mes[i].y=i*2; mes[i].z=3*i/2;
        }
        shmdt(mes);
        return 0;
    }
}
