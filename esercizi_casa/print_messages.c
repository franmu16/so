#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
pid_t pid;
int i=1;
char* s=argv[i];
while(s!=NULL){
  pid= fork();
  void srand(pid);
  if (pid == 0) { /* processo figlio */
    sleep(rand() % 11);
    printf("PID: %d,  Messaggio: %s\n", pid, argv[i]);
  }
  else if (pid > 0) { /* processo padre */
    wait(NULL);
    return(0);
  }
  i++;
  s=argv[i];
}
return 0;
}
