#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define size 3

void Calcola_radici(int*v, float*r1, float*r2){
    int det = (v[1])*(v[1]) - 4*v[0]*v[2];
    if (det >= 0) {
        *r1 = (-v[1] + sqrt(det)) / (2.0 * v[0]);
        *r2 = (-v[1] - sqrt(det)) / (2.0 * v[0]);
    } 
    else{
        // Gestione delle radici complesse o immaginarie
        printf("Le radici sono complesse o immaginarie.\n");
    }
}


int main(){
    int fd[2];
    int v[size];
    int ret = pipe(fd);
    if(ret<0){
        printf("Errore pipe");
        return 1;
    }
    printf("Inserire valori a,b,c: ");
    scanf("%d %d %d", v,v+1,v+2);
    int sent = write(fd[1], v, sizeof(v));
    if(sent<sizeof(v))
        printf("Errore in invio");
    pid_t pid = fork();
    if(pid<0){
        printf("Errore fork");
        return 1;
    }
    if(pid==0){
        close(fd[1]);
        float r1,r2;
        int vet[size];
        int rcv = read(fd[0], vet, sizeof(vet));
        if(rcv<sizeof(v))
            printf("Errore in ricezione");
        Calcola_radici(vet,&r1,&r2);
        printf("1a radice: %f\n2a radice: %f\n", r1,r2);
        close(fd[0]);
    }
    if(pid>0){
        wait(NULL);
        printf("Terminazione con successo del processo padre");
        close(fd);
    }
    return 0;
}

