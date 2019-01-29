#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(int argc, char const *argv[])
{
	int fork_id;

	fork_id = fork();
	if(fork_id > 0) {
		wait(NULL);
		printf("Parent(%d): Done\n", getpid());
	} else {
		execl("./file2", "file2", argv[1], argv[2], NULL);
	}

	return 0;
}