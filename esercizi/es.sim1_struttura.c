#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define SIZE 100
typedef struct{
    char str[SIZE];
}shared_data;
int main(int argc, char* argv[]){
    int i,len;
    char tmp;
    len=strlen(argv[1]);
    int segment_id = shmget(IPC_PRIVATE, sizeof(shared_data), S_IRUSR | S_IWUSR);
    if(segment_id<0){
      printf("Errore di allocazione memoria condivisa");
      return 1;
    }
    pid_t pid = fork();
    if(pid<0){
      printf("Errore della fork\n");
      shmctl(segment_id, IPC_RMID, NULL);
      return 1;
    }
    else if(pid==0){
        shared_data* s=(shared_data*)shmat(segment_id,NULL,0);
        strncpy(s->str, argv[1],len);
        for (i = 0; i < len / 2; i++) {
            tmp = s->str[len - i - 1];
            s->str[len - i - 1] = s->str[i];
            s->str[i] = tmp;
        }
        shmdt(s);
        return 0;
    }    
    if(pid>0){
        wait(NULL);
        shared_data* s=(shared_data*)shmat(segment_id,NULL,0);
        printf("%s",s->str);
        shmdt(s);
        shmctl(segment_id, IPC_RMID, NULL);
        return 0;
    }
    return 0;
}
