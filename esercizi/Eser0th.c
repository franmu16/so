#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* Struttura usata per scambiare informazioni col thread */
/* Prototipo della funzione che verrà eseguita dal thread */
void *func(void *arg);
int main(int argc, char *argv[]) {
  int i;
 if (argc!=2) {
  printf("Devi specificare un numero intero come parametro!\n");
 return 1;
 }
 int numero = atoi(argv[1]);
 int arg[numero];
 pthread_t tid[numero]; /* Identificativo del nuovo thread */
 for (i=0; i<numero; i++){
  arg[i]=i;
  if (pthread_create(&tid[i], NULL, func, &arg[i])!=0) {
    printf("Errore nella creazione del thread!\n");
    return 2;
  }
 }
 /* Aspetta la fine del thread */
 for(i=0; i<numero; i++){
  pthread_join(tid[i], NULL);
 }
 return 0;
}

void *func(void *arg) {
 int n=*(int*)arg;
 printf("Numero=%d\n", n);
 return NULL;
}

