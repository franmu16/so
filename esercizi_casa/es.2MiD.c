#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int genera(int num){
    int i=2, flag=0;
    do{
        if(num%i==0)
            flag=1;
        i++;
        if(flag==1)
            return 1;
    }while(i<num);
    return flag;
}
int main(int argc, char *argv[]){
    int i, fd[2];
    int r = pipe(fd);
    if(r!=0){
        printf("Errore della pipe");
        return 1;
    }
    pid_t pid = fork();
    if(pid<0){
        printf("Errore fork");
        return 1;
    }
    if(pid==0){
        close(fd[0]);
        int k=0,result;
        int sent;
        int num = atoi(argv[1]);
        do{
            num=num+1;
            result=genera(num);
            if(result==0){
                sent=write(fd[1],&num, sizeof(num));
                if(sent<sizeof(num))
                    printf("Errore in invio");
                k++;
            }
        }while(k<2);
        close(fd[1]);
    }
    if(pid>0){
        close(fd[1]);
        int i=0,num;
        while(i<2){
            int rcv = read(fd[0], &num, sizeof(int));
            printf("%do numero primo: %d\n",i+1, num);
            if(rcv<sizeof(int))
                printf("Errore in lettura");
            i++;
        }
        close(fd[0]);
    }

    return 0;
}

