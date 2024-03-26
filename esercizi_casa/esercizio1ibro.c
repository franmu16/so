#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int value = 5;
int main()
{
pid_t pid;
pid = fork();
if (pid == 0) { /* processo figlio */
value= value + 15;
printf("VALUE= %d\n",value);
return 0;
}
else if (pid > 0) { /* processo padre */
wait(NULL);
printf("PARENT: value = %d",value); /* LINEA A */
return 0;
}
}


