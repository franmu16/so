/* esercizio sava
Il programma prevede di ricevere da linea di comando un numero pari N, 1<N<51.
Si creino N threads, di cui la prima metà sono produttori e la seconda i consumatori.
Ogni produttore  ha un proprio id che va da 1 a N/2
Ogni consumatore ha un proprio id che va da 1 a N/2 

Ogni produttore chiede da tastiera un numero int, attraverso un prompt che deve 
specificare il proprio id: (N=10) output ->
PRODUTTORE (id=4) -> richiedo stringa: ciaoo
Ora può riempire il buffer condiviso 

Ogni consumatore legge dal buffer, stampando:
CONSUMATORE (id=10) -> prelevo stringa: caioo, dal produttore (id=4)

Si adotti un'implementazione della sincronizzazione tramite l'utilizzo di due 
condvar (libero,occupato) da parte dei produttori e consumatori, nonostante ne basti una.

Il thread principale è in attesa infinita, per cui il programma non deve terminare
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{
    int x;
    char str[100];
}Telementi;

typedef struct{
    Telementi e;
    bool completo;
    pthread_mutex_t mutex;
    pthread_cond_t libero;
    pthread_cond_t occupato;
}TBuffer;

typedef struct{
    int id;
    TBuffer* buffer;
}Tparam;

void* produttore(void*);
void* consumatore(void*);

int main(int argc, char* argv[]){
    //INSERIRE IL CODICE
    int N,i;
    printf("Inserire valore N: ");
    scanf("%d", &N);
    Tparam p[N];
    TBuffer b;
    Telementi t=b.e;
    pthread_mutex_init(&b.mutex,NULL);
    pthread_cond_init(&b.libero, NULL);
    pthread_cond_init(&b.occupato, NULL);
    b.completo=false;
    pthread_t tid[N];
    for(i=0; i<N/2; i++){
        p[i].buffer=&b;
        p[i].id=i;
        pthread_create(&tid[i], NULL, produttore, &p[i]);
    }
    for(i=N/2; i<N; i++){
        p[i].buffer=&b;
        p[i].id=i;
        pthread_create(&tid[i], NULL, consumatore, &p[i]);
    }
    for(i=0; i<N; i++){
        pthread_join(tid[i],NULL);
    }
}

void* produttore(void* arg){
    //INSERIRE IL CODICE
    Tparam* p = (Tparam*) arg;
    TBuffer* b = p->buffer;
    while(1){
        pthread_mutex_lock(&b->mutex);
        while(b->completo==true)
            pthread_cond_wait(&b->occupato, &b->mutex);
        printf("PRODUTTORE (id=%d) -> richiedo stringa: ", p->id);
        scanf("%s", b->e.str);
        b->completo=true;
        printf("%d", p->id);
        b->e.x=p->id;
        pthread_mutex_unlock(&b->mutex);
        pthread_cond_broadcast(&b->libero);
    }
    
}

void* consumatore(void* arg){
    //INSERIRE IL CODICE 
    Tparam* p = (Tparam*) arg;
    TBuffer* b = p->buffer;
    while(1){
        pthread_mutex_lock(&b->mutex);
        while(b->completo==false)
            pthread_cond_wait(&b->libero, &b->mutex);
        printf("CONSUMATORE (id=%d) -> prelevo stringa: %s, dal produttore (id=%d)\n", p->id, b->e.str, b->e.x);
        b->completo=false;
        pthread_mutex_unlock(&b->mutex);
        pthread_cond_broadcast(&b->occupato);
    }
    
}
