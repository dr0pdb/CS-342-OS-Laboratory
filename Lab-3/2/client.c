#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(int argc, char const *argv[])
{
	char a[15],b[15];
	int child_id, status;
	char opr[2];
	while(1) {
		printf("Please enter the two numbers and the operator(num1 num2 operator): ");
		scanf("%s %s %s", a, opr, b);
		child_id = fork();

		if(child_id > 0) {
			wait(&status);
			printf("The returned answer is %d\n", WEXITSTATUS(status));
		} else {
			execl("./server", "server", a, b, opr, NULL);
		}
	}
	return 0;
}