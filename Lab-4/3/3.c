#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *Busy( void *tid )
{
	sleep(1);
 	pthread_exit((void*) 0);
}

int main(int argc, char const *argv[])
{
	pthread_t threadid[5];
	int return_codes[5];
	for (int i = 0; i < 5; ++i)
	{
		printf("Creating thread %d\n", i);
		return_codes[i] = pthread_create(&threadid[i], NULL, Busy, (void *)threadid[i]);
		if(return_codes[i] != 0) {
			printf("ERROR: Return code from pthread_create for thread %d is %d\n", i, return_codes[i]);
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_t status = pthread_join(threadid[i], NULL);
		if(status != 0) {
			printf("ERROR: Return code from pthread_join for thread %d is %ld\n", i, status);			
		} else {
			printf("Completed join with thread %ld with status %ld\n", threadid[i], status);			
		}
	}

	printf("Exiting from the program\n");
	return 0;
}