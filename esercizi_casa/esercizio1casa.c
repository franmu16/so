#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
pid_t pid1,pid2;
pid1 = fork();
if (pid1 == 0) { /* processo figlio */
printf("PID fork figlio1: %d  PID proprio: %d\n",pid1,getpid());
pid2= fork();
if (pid2 == 0) { /* processo figlio */
printf("PID fork figlio2: %d  PID proprio: %d\n",pid2,getpid());
}
else if (pid2 > 0) { /* processo padre */
wait(NULL);
printf("PID fork padre2: %d  PID proprio: %d\n",pid2,getpid());
exit(0);
}
}
else if (pid1 > 0) { /* processo padre */
wait(NULL);
printf("PID fork padre1: %d  PID proprio: %d\n",pid1,getpid());
exit(0);
}
return 0;
}
