#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int static_variable = 0;
int global_variable = 0;

void increment_static_variable() {
	static_variable++;
}

void incremenet_global_variable() {
	global_variable++;
}

void increment_local_variable(int *local_variable) {
	(*local_variable)++;
}

void *print_message_function( void *ptr )
{
	int local_variable = 0, thread_number = (int)ptr;
 	printf("Incrementing static variable in thread %d\n", thread_number);
 	increment_static_variable();
 	printf("The value of static variable in thread %d is %d\n", thread_number, static_variable);
	printf("Incrementing global variable in thread %d\n", thread_number);
 	incremenet_global_variable();
 	printf("The value of global variable in thread %d is %d\n", thread_number, global_variable);
 	printf("Incrementing local variable in thread %d\n", thread_number);
 	increment_local_variable(&local_variable);
 	printf("The value of local variable in thread %d is %d\n", thread_number, local_variable);
 	pthread_exit((void*) 0);
}

int main(int argc, char const *argv[])
{
	pthread_t threadid[5];
	for (int i = 0; i < 5; ++i)
	{
		int num = i;
	 	printf("Thread created with id: %d\n", num);
		pthread_create(&threadid[i], NULL, print_message_function, (void *)num);
	}

	for (int i = 0; i < 5; ++i)
	{
		pthread_join(threadid[i], NULL);		
	}
	return 0;
}