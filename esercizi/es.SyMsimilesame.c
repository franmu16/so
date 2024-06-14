/*-------------------------------------------------------------------
 * Completare il programma fornito, completando il main e
 * implementando la funzione worker_thread.
 * Il main deve creare 100 thread figli, a cui deve passare
 * come parametri un intero da 1 a 100 (diverso per ogni thread figlio)
 * e un buffer che può contenere un singolo numero intero.
 * Una volta che i thread figli sono stati creati, il main deve
 * eseguire il seguente algoritmo:
 *         1. Ripeti per 100 volte i passi da 2 a 4.
 *           2. Aspetta che il buffer sia pieno.
 *           3. Preleva il valore contenuto nel buffer e stampalo a video
 *           4. Rendi il buffer vuoto.
 *
 * I thread figli, che eseguono la funzione worker_thread, devono svolgere
 * il seguente algoritmo:
 *           1. Aspetta 3 secondi.
 *           2. Aspetta che il buffer sia vuoto.
 *           3. Inserisci il numero ricevuto come parametro nel buffer.
 *           4. Rendi il buffer pieno.
 *
 * È necessario gestire in maniera appropriata la sincronizzazione dei
 * thread (incluso il main) nell'accesso al buffer.
 *
 * ESEMPIO
 * Lanciando il programma, l'ouput deve essere simile al seguente:
 *    Ho ricevuto il numero: 1
 *    Ho ricevuto il numero: 94
 *    Ho ricevuto il numero: 59
 *    Ho ricevuto il numero: 19
 *    Ho ricevuto il numero: 22
 *            . . . ( altri valori omessi per brevità ) . . .
 *    Ho ricevuto il numero: 39
 *    Ho ricevuto il numero: 40
 *    Ho ricevuto il numero: 51
 *    Ho ricevuto il numero: 56
 *
 *
 --------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_WORKERS 100

/* Tipo da usare per il buffer */
typedef struct {
    int valore;   /* Valore contenuto nel buffer */
    bool pieno;   /* true se il buffer contiene un valore */
    pthread_mutex_t mutex; /* Mutex per l'accesso al buffer */
    pthread_cond_t  cond;  /* Condition per l'accesso al buffer */
} TBuffer;

/* Tipo da usare per passare i parametri ai thread figli */
typedef struct {
    int numero;   /* Numero assegnato al thread */
    TBuffer *buffer; /* Puntatore al buffer */
} TWorkerParam;


/* Prototipo della funzione dei thread figli */
void *worker_thread(void *param);



int main(int argc, char *argv[])
{
    TWorkerParam t[NUM_WORKERS];
    TBuffer s;
    pthread_t tid[NUM_WORKERS];
    int i;
    pthread_mutex_init(&s.mutex, NULL);
    pthread_cond_init(&s.cond, NULL);
    s.pieno=false;
    for(i=0; i<NUM_WORKERS; i++){
        t[i].buffer=&s;
        t[i].numero=i;
        pthread_create(tid+i, NULL, worker_thread, &t[i]);
    }
    for(i=0; i<NUM_WORKERS; i++){
        pthread_mutex_lock(&s.mutex);
        while(s.pieno==false)
            pthread_cond_wait(&s.cond, &s.mutex);
        printf("Ho ricevuto il numero: %d\n", s.valore);
        s.pieno=false;
        pthread_mutex_unlock(&s.mutex);
        pthread_cond_broadcast(&s.cond);
    }
    

    return 0;
}

void *worker_thread(void *param) {
    /* INSERIRE IL CODICE */
    TWorkerParam* t = (TWorkerParam* ) param;
    TBuffer* s = t->buffer;
    pthread_mutex_lock(&s->mutex);
    while(s->pieno==true)
        pthread_cond_wait(&s->cond, &s->mutex);
    sleep(3);
    s->valore=t->numero;
    s->pieno=true;
    pthread_mutex_unlock(&s->mutex);
    pthread_cond_broadcast(&s->cond);

    return NULL;
}
