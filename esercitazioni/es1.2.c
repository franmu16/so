#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    unsigned int tP=2;
    unsigned int tC=5;
    printf("Main:");
    printf("PID=%d; My parent's PID= %d\n",getpid(),getppid());    
    // fork a child process
    pid = fork();

    
    if(pid < 0) {
        // error occurred
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else
        //printf("Fork value: %d",pid);
        if (pid == 0) {
            // child process
            sleep(tC);
            printf("Child: PID returned= %d", pid);
            printf("PID=%d; My parent's PID= %d\n",getpid(),getppid()); 
        } else {
            // parent process
            sleep(tP);
            printf("Father: PID returned= %d", pid); 
            printf("PID=%d; My parent's PID= %d\n",getpid(),getppid()); 
        }
    fprintf(stdout, "Program completed!\n");
}

