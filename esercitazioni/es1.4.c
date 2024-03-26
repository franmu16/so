#include <pthread.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int global_val=0;
int main(){
	int* local_val= (int *)malloc(sizeof(int));
	*local_val=1;
	pid_t pid;
	pid = fork();
	if(pid<0){
		fprintf(stderr, "Fork Failed\n");
		exit(1);
	}
	if(pid==0){
		global_val=100;
		*local_val=*local_val+1;
		printf("FIGLIO: Globale: %d, locale: %d\n", global_val, *local_val);
		exit(0);
	}
	else
		wait(NULL);
		printf("PADRE:Variabile globale: %d, variabile locale: %d\n",global_val, *local_val);
	return 0;


}
