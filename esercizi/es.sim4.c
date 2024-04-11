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
  int fd1[2];
  shared_data data;
  int len=strlen(argv[1]);
  strncpy(data.str,argv[1], SIZE);
  int retval=pipe(fd1);
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
    close(fd1[0]);
    char* test[SIZE];
    strncpy(test, data.str, SIZE);
    int fd2[2];
    int rval=pipe(fd2);
    if(rval<0){
      printf("Errore della pipe");
    return 1;
    }
    pid_t pid2=fork();
    if(pid2<0){
      printf("Errore della fork");
      return 1;
    }
    if(pid2==0){
    for(i=0; i<len/2; i++){
      char tmp = data.str[i];
      data.str[i]=data.str[len-i-1];
      data.str[len-i-1]=tmp; 
    }
    int sent = write(fd1[1], &data,  sizeof(data));
    int sent = write(fd2[1], &data,  sizeof(data));
    if(sent<sizeof(shared_data))
      printf("Errore nell'invio");
    }
    if(pid2>0){
      close(fd2[1]);
      char* t1[SIZE];
      char* t2[SIZE];
      int rcv = read(fd2[0], t, sizeof(data));
      if(strcmp(t1,t2)==0)
        printf("Stringa palindroma");
      else
        printf("Stringa non palindroma");
    }
  }
  else if(pid>0){
    close(fd1[1]);
    shared_data d;
    int received = read(fd1[0], &d, sizeof(data));
    if(received<sizeof(shared_data))
      printf("Errore in ricezione");
    printf("%s", d.str);
    close(fd1[0]);
  }
}
