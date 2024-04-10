#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 100
int leggi_numeri(int fd, int* r){
    int conta=0,receive;
    do{
        receive =(int) read(fd, r+conta/sizeof(int), 5*sizeof(int));
        if(receive<0){
            printf("Errore in lettura");
            return 1;
        }
        if(receive<sizeof(int))
            printf("Messaggio incompleto");
        conta=conta+receive;
    }while(conta!=5*sizeof(int));
    return conta;
}
int main(int argc, char* argv[]) {
 int fd[2], i, v[5];
 pid_t pid;
 int retval=pipe(fd);
 if(retval!=0){
    printf("Errore nella creazione della pipe");
    return 1;
 }  
 pid=fork();
 if(pid<0){
     printf("Errore della fork");
     return 1;
 }
 if(pid==0){
    close (fd[0]);
    for(i=0; i<5; i++){
        printf("Inserire numero: ");
        scanf("%d", v+i);
    }
    int sent = write(fd[1],v, 2*sizeof(int));
    if(sent!=2*sizeof(int))
        printf("Errore nell'invio");
    sleep(1);
    sent = write(fd[1],v+2, 3*sizeof(int));
    if(sent!=3*sizeof(int))
        printf("Errore nell'invio");
    close(fd[1]);
    return 0;
 }
 if(pid>0){
     close(fd[1]);
     int v[5];
     int ricevuti= leggi_numeri(fd[0],v);
     if(ricevuti<5)
        printf("Ricezione parziale");
     else
        for(i=0; i<5; i++)
            printf("%d", v[i]);
    close(fd[0]);
    return 0;
 }
 
}
