#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long long int factorial(int n) {
	long long int ret = 1;
	for (int i = 2; i <= n; ++i)
	{
		ret *= i;
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	int fork_id, n;
	printf("Please enter a number to know it's factorial(n <= 10): ");
	scanf("%d", &n);

	fork_id = fork();

	if(fork_id == 0) {
		long long int fact = factorial(n);
		printf("The value of %d! from the child process(id: %d) is %lld\n", n, getpid(), fact);
	} else {
		long long int fact = factorial(n);
		printf("The value of %d! from the parent process(id: %d) is %lld\n", n, getpid(), fact);
	}

	return 0;
}