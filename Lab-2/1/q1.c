#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int fork_id;
	fork_id = fork();

	if(fork_id == 0) {
		printf("I am the child process with id: %d and my parent's id is: %d\n", getpid(), getppid());
	} else {
		printf("I am the parent process with id: %d and my child's id is %d\n", getpid(), fork_id);
	}

	return 0;
}