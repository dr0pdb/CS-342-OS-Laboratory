#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(int argc, char const *argv[])
{
	char file_name[50];
	strcpy(file_name, argv[1]);

	int fork_id = fork();
	if(fork_id == 0) {
		char command[100]="./dstring ";
		strcat(command, file_name);
		// execl("/usr/bin/xterm", "/usr/bin/xterm", "-e", "bash", "-c", "./dstring",file_name, (void*)NULL);
		execl("/usr/bin/xterm", "/usr/bin/xterm", "-hold" ,"-e", "bash", "-l", "-c", command,(void*)NULL);
	} else {
		wait(NULL);
	}

	return 0;
}