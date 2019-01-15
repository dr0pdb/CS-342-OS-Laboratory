#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

int main(int argc, char const *argv[])
{
	if(argc == 1) {
		printf("Please enter an integer as argument.\n");
		return 0;
	} 

	int fork_id, t;
	t = atoi(argv[1]); // getting the time to sleep.

	fork_id = fork();

	if(fork_id == 0) {
		printf("----The list of processes from the child process-----\n");
		system("ps");
		printf("\nSleeping the child process for %d seconds\n", t);
		sleep(t);
		printf("Child process is done sleeping.\n");
	} else {
		printf("Parent process is waiting for child process.\n");
		wait(NULL);
		printf("Parent process is done waiting for child process.\n");
		printf("\n----The list of processes from the parent process-----\n");
		system("ps");
	}

	return 0;
}