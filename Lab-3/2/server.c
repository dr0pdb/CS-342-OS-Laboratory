#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(int argc, char const *argv[])
{
	int a,b,ans = 0; 
	char opr;
	a = atoi(argv[1]),b = atoi(argv[2]);
	opr = (char)argv[3][0];

	switch(opr) {
		case '+':
			ans = a + b;
			break;
		case '-':
			ans = a - b;
			break;
	}
	
	return ans;
}