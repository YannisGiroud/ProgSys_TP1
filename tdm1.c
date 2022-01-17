#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void print_PCB()
{
	pid_t PID = getpid();
	pid_t PPID = getppid();
	pid_t UID = getuid();
	pid_t GID = getgid();
	printf("PID = %d\n PPID = %d\n UID = %d\n GID = %d\n",PID,PPID,UID,GID);
}

int main()
{
	pid_t ret = fork();
	printf("fork() has returned: %d\n", ret);
	print_PCB();
	exit(EXIT_SUCCESS);
}
