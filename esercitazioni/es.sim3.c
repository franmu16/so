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
    int segment_id = shmget(IPC_PRIVATE, len, S_IRUSR | S_IWUSR);
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
        pid_t pid2=fork();
        if(pid2<0){
            printf("Errore fork");
            shmctl(segment_id, IPC_RMID, NULL);
            return 1;
        }
        if(pid2>0){
            char* s=(char*)shmat(segment_id,NULL,0);
            strncpy(s, argv[1],len);
            for (i = 0; i < len / 2; i++) {
                tmp = s[len - i - 1];
                s[len - i - 1] = s[i];
                s[i] = tmp;
            }
            shmdt(s);
        }
        if(pid2==0){
            char* m=(char*)shmat(segment_id,NULL,0);
            char orig[SIZE];   
            strncpy(orig,argv[1],SIZE);  
            wait(NULL);
            if(strcmp(m,orig)==0)
                printf("Stringa palindroma ");
            else
                printf("Stringa non palindroma ");
            shmdt(m);
        }
        
        return 0;
    }    
    if(pid>0){
        wait(NULL);
        char* s=(char*)shmat(segment_id,NULL,0);
        printf("%s",s);
        shmdt(s);
        shmctl(segment_id, IPC_RMID, NULL);
        return 0;
    }
    return 0;
}
