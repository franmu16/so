#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
    int fd[2], i, n,num;

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
        close(fd[0]); // Close read pipe
        // Compose message
        num=atoi(argv[1]);
        int sent = (int)write(fd[1], &num, sizeof(num));
        if (sent != sizeof(num)) {
            printf("Sending error!\n");
            return 1;
        }
        close(fd[1]);
        return 0;
    } else {
        // Father process
        close(fd[1]); // Close write pipe
        int received = (int)read(fd[0], &num, sizeof(num));
        if (received < 0) {
            printf("Receiving error!\n");
        } else {
            if (received < sizeof(num))
                printf("Messagge incomplete!\n");
            // verify bytes received
            n = received/(int)sizeof(int);
            printf("%d ", num);
            printf("\n");
        }
        close(fd[0]);
        return 0;
    }
}

