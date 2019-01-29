#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t odd, even;

void *printEvenNumbers( void *args) {
	for(int i = 2; i <= 100; i+=2) {
		sem_wait(&even);
		printf("%d\n", i);
		sem_post(&odd);
	}
	pthread_exit((void*) 0);
}

int main(int argc, char const *argv[])
{
	sem_init(&odd, 0, 1);
	sem_init(&even, 0, 0);
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, printEvenNumbers, NULL);
	for (int i = 1; i <= 100; i+=2)
	{
		sem_wait(&odd);
		printf("%d\n", i);
		sem_post(&even);
	}
	pthread_join(thread_id, NULL);
	return 0;
}