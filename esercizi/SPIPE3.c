#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 100
struct crd{
  float x;
  float y;
  float z;
};
typedef struct crd cord;
int main(int argc, char* argv[]) {
    int fd[2], i, n;
    cord message;

    if (pipe(fd) < 0) {
        printf("Pipe creation error\n");
        return 1;
    }
    pid_t pid = fork();
    if (pid<0) {
        printf("fork error\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        close(fd[1]); // Close write pipe
        for(i=0; i<50; i++){
        int received = (int)read(fd[0], &message, sizeof(message));
        if (received < 0) {
            printf("Receiving error!\n");
        } else {
            if (received < sizeof(message))
                printf("Message incomplete!\n");
            printf("%f %f %f", message.x, message.y, message.z);
                 printf("\n");
        }
        }
        close(fd[0]);
        return 0;
    } else {
        // Father process
        close(fd[0]); // Close read pipe
        // Compose message
        for(i=0; i<50; i++){
          message.x=i; message.y=i*2; message.z=3*i/2;
          int sent = (int)write(fd[1], &message, sizeof(cord));
          if (sent != sizeof(message)) {
             printf("Sending error!\n");
             return 1;
          }
        }
        close(fd[1]);
        return 0;
    }
}
