#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr )
{
 	pthread_t thread_id = *(pthread_t*)ptr;
 	printf("CSE OS lab by thread id: %lu\n", thread_id);
 	pthread_exit((void*) 0);
}

int main(int argc, char const *argv[])
{
	pthread_t threadid[3];
	for (int i = 0; i < 3; ++i)
	{
		pthread_create(&threadid[i], NULL, print_message_function, &threadid[i]);
	}

	for (int i = 0; i < 3; ++i)
	{
		pthread_join(threadid[i], NULL);		
	}
	return 0;
}