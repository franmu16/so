#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define SIZE 50

typedef struct {
  char str[SIZE];
}shared_data;

int main(int argc, char* argv[]){
  int fd[2];
  shared_data data;
  int len=strlen(argv[1]);
  strncpy(data.str,argv[1], SIZE);
  int retval=pipe(fd);
  if(retval<0){
    printf("Errore della pipe");
    return 1;
  }
  pid_t pid=fork();
  if(pid<0){
    printf("Errore della fork");
    return 1;
  }
  if(pid==0){
    int i;
    close(fd[0]);
    for(i=0; i<len/2; i++){
      char tmp = data.str[i];
      data.str[i]=data.str[len-i-1];
      data.str[len-i-1]=tmp; 
    }
    int sent = write(fd[1], &data,  sizeof(data));
    if(sent<sizeof(shared_data))
      printf("Errore nell'invio");
    close(fd[1]);
  }
  else if(pid>0){
    close(fd[1]);
    shared_data d;
    int received = read(fd[0], &d, sizeof(data));
    if(received<sizeof(shared_data))
      printf("Errore in ricezione");
    printf("%s", d.str);
    close(fd[0]);
  }
}
