#include <pthread.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	
	pid = fork();
	if(pid<0){
		fprintf(stderr, "Fork Failed\n");
		exit(1);
	}
	if(pid==0){
		printf("Father's PID: %d", getpid());
		execlp("/bin/ls","ls","-al",NULL);
		printf("I am the line after executing directory listing: ls -al\n");
	}
	else
		wait(NULL);
	return 0;


}
