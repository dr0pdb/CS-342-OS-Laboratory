#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_counter=0;

int main(int argc, char const *argv[])
{
	int fork_id;

	global_counter++; // counter should be 1 now.
	printf("The value of global_counter before fork is %d\n", global_counter);
	fork_id = fork();

	if(fork_id == 0) {
		printf("Adding 10 to global_counter in the child process\n");
		global_counter += 10;
		printf("The value of global_counter in child process is %d\n", global_counter);
	} else {
		printf("Adding 2 to global_counter in the parent process\n");
		global_counter += 2;
		printf("The value of global_counter in parent process is %d\n", global_counter);
	}

	return 0;
}