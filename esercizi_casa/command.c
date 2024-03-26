#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
pid_t pid1;
char s1[]="/bin/";
pid1=fork();
if (pid1 == 0) { /* processo figlio */
strcat(s1,argv[1]);
execlp(s1, argv[1], NULL);
}
else if (pid1 > 0) { /* processo padre */
wait(NULL);
printf("Comando eseguito!");
exit(0);
}
return 0;
}
