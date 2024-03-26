#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 5

int read_message(int fd, int* vet, int num){
  int conta=0;
  do{
        int received = (int)read(fd, vet+conta/sizeof(int), num*sizeof(int));
        if (received < 0) {
            printf("Receiving error!\n");
        } else {
            if (received < sizeof(int))
                printf("Message incomplete!\n");
    conta += received;
    } }while(conta!= num*sizeof(int));
    return conta;
    }
int main(int argc, char* argv[]) {
    int fd[2], i, n;
    int message[N];

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
        for(i=0; i<N; i++){
          printf("Digitare numero: ");
          scanf("%d",&message[i]);
        }
        int sent = (int)write(fd[1], message, 2*sizeof(int));
        if (sent != 2*sizeof(int)) {
            printf("Sending error!\n");
            return 1;
        }
        sleep(1);
        sent = (int)write(fd[1], message+2, 3*sizeof(int));
        if (sent != 3*sizeof(int)) {
            printf("Sending error!\n");
            return 1;
        }
        close(fd[1]);
        return 0;
    } else {
        // Father process
       close(fd[1]); // Close write pipe
       int ricevuti=read_message(fd[0], message, N);
       if(ricevuti<sizeof(message))
        printf("Errore");
      else
        for(i=0; i<N; i++)
        printf("%d ", message[i]);
       }
       
       
}

