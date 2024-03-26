#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define N 100
int main(int argc, char* argv[]) {
    int fd[2], i, n;
    char message[N];
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    printf("%ld", begin.tv_usec);
    if(argc < 2){
      printf("Nome non inserito!");
      return 0;
    }

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
        int received = (int)read(fd[0], message, sizeof(message));
        if (received < 0) {
            printf("Receiving error!\n");
        } else {
            if (received < sizeof(argv[1]))
                printf("Message incomplete!\n");
            char c[]="/bin/";
            strcat(c,message); 
            execlp(c,argv[1],NULL);     
        }
        close(fd[0]);
        return 0;
    } else {
        // Father process
        close(fd[0]); // Close read pipe
        // Compose message
        
        int sent = (int)write(fd[1], argv[1], sizeof(argv[1]));
        if (sent != sizeof(argv[1])) {
            printf("Sending error!\n");
            return 1;
        }
        gettimeofday(&end, NULL);
        double durata = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec) / 1000000.0);
        printf("Durata esecuzione in millisecondi: %f", durata);
        close(fd[1]);
        return 0;
    }
}

