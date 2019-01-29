#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(int argc, char const *argv[])
{
	int fd[2];  // Used to store two ends of first pipe 
    char input_string[100]; // Input by the user.

    if (pipe(fd)==-1) 
    { 
        fprintf(stderr, "Pipe Failed!"); 
        return 1; 
    }
  
  	printf("Please enter a string: ");
    scanf("%s", input_string);

	int fork_id;
	fork_id = fork();

	if(fork_id == 0) {
		// closing the write end of child.
		close(fd[1]);
		char buffer[100];

		read(fd[0], buffer, 100);
		printf("Child: Read %s from the pipe\n", buffer);
		close(fd[0]);
	} else {
		// closing the read end of the parent.
		close(fd[0]);

		printf("Parent: Writing %s on the pipe\n", input_string);
		fflush(stdin);
		write(fd[1], input_string, strlen(input_string)+1);
		close(fd[1]);
	}
	return 0;
}