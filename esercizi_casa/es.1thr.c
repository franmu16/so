#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
typedef struct{
  float *v;
  int n;
}data;
void *radice(void *arg){
  data* s = (data*) arg;
  for(int i=0; i<s->n; i++){
    s->v[i] = sqrt(s->v[i]);
  }
}
int main(int argc, char *argv[]) {
  data str1,str2;
  int i;
  if(argc!= 2){
    printf("Non element");
    return 0;
  }
  int n = atoi(argv[1]);
  float v[n];
  str1.n = n/2;
  str1.v = v;
 for(i=0; i<n; i++){
  v[i] = (float) i+1;
 }
 pthread_t th1,th2;
 pthread_create(&th1, NULL, radice, &str1);
 if(th1<0){
    printf("Errore thread");
    return 0;
  }
  str2.n = n-n/2;
  str2.v = v+(n/2);
 pthread_create(&th2, NULL, radice, &str2);
 if(th2<0){
    printf("Errore thread");
    return 0;
  }
 pthread_join(th1, NULL);
 pthread_join(th2, NULL);
 for(i=0; i<n; i++){
  printf("%f  ", v[i]);
 }
 return 0;
}
