#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *printEvenNumbers( void *args) {
	for(int i = 2; i <= 100; i+=2) {
		printf("%d\n", i);
	}
	pthread_exit((void*) 0);
}

int main(int argc, char const *argv[])
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, printEvenNumbers, NULL);
	for (int i = 1; i <= 100; i+=2)
	{
		printf("%d\n", i);
	}
	pthread_join(thread_id, NULL);
	return 0;
}