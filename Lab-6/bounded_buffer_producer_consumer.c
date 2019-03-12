#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 10

// global variables.
pthread_mutex_t mutex;
sem_t full, empty;
int buffer[BUFFER_SIZE], counter;
pthread_t tid;

// initializes semaphores and counter.
void initializeData() {
   pthread_mutex_init(&mutex, NULL);
   sem_init(&full, 0, 0);
   sem_init(&empty, 0, BUFFER_SIZE);
   counter = 0;
}

int insert_item(int item) {
	if(counter < BUFFER_SIZE) {
		buffer[counter] = item;
		counter++;
		return 0;
	}
	else {
		return -1;
	}	
}

int remove_item(int *item) {
	if(counter > 0) {
		*item = buffer[(counter-1)];
		counter--;
		return 0;
	}
	else {
		return -1;
	}
}

void *producer_function(void *param) {
	int id = (int) param;
	int item;

	while(1) {
		// sleep for random time.
		int random_num = rand() % 2;
		sleep(random_num);

		// generate a random number to produce.
		item = rand();

		sem_wait(&empty); // check if the buffer is full or not.
		pthread_mutex_lock(&mutex); // aquire the buffer sem.

		if(insert_item(item)) {
			printf("producer %d error\n", id);
			fflush(stdout);
		}
		else {
			printf("producer %d produced %d\n", id, item);
			fflush(stdout);
		}
 
		pthread_mutex_unlock(&mutex); // release.
		sem_post(&full); // wake up any consumer threads.
	}
}

void *consumer_function(void *param) {
	int item, id;
	id = (int) param;

	while(1) {
		// sleep for a random time.
		int random_num = rand() % 2;
		sleep(random_num);

		// check if the buffer is empty or not.
		sem_wait(&full);
		pthread_mutex_lock(&mutex); // aquire the buffer sem.
		
		if(remove_item(&item)) {
			printf("consumer %d error\n", id);
			fflush(stdout);
		}
		else {
			printf("consumer %d consumed %d\n", id, item);
			fflush(stdout);
		}
		
		pthread_mutex_unlock(&mutex); // unlock.
		sem_post(&empty);
	}
}

int main(int argc, char *argv[]) {
	int i;

	// checking args
	if(argc != 4) {
		printf("Please provide (sleep time #producers #consumers)\n");
		return 1;
	}

	// parsing from command line.
	int sleeping_time = atoi(argv[1]);
	int num_producers = atoi(argv[2]);
	int num_consumers = atoi(argv[3]);

	// data initialization.
	initializeData();

	// creating threads.
	for(i = 0; i < num_producers; i++) {
		pthread_create(&tid, NULL, producer_function, (void *)i);
	}

	for(i = 0; i < num_consumers; i++) {
		pthread_create(&tid, NULL,consumer_function, (void *)i);
	}

	// sleeping now.
	printf("Main thread sleeping now for %d seconds\n", sleeping_time);
	sleep(sleeping_time);

	/* Exit the program */
	printf("Main program is done sleeping. Terminating program now\n");
	exit(0);
}