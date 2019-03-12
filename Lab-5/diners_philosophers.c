#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

#define num_philosophers 5

int left(int index) {
	return (index) % num_philosophers;
}

int right(int index) {
	return (index + 1) % num_philosophers;
}

sem_t sem_print, sem_allocation_resource, sem_forks[num_philosophers];
int eating=0; // number of philosophers eating at this moment.
int fork_status[num_philosophers]; // status of each fork, 1 denotes free.
int a[num_philosophers][num_philosophers]; // allocation matrix.
int r[num_philosophers][num_philosophers]; // resource matrix.
pthread_t thread_id[num_philosophers]; // thread id.
int done[num_philosophers]; // number of threads that are done.

// prints the allocation and request matrix.
void print_matrices()
{
	sem_wait(&sem_print);
	printf("Allocation Matrix : \n");
	for(int i = 0; i < num_philosophers; i++){
		for(int j = 0; j < num_philosophers; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
	printf("\nRequest Matrix : \n");
	for(int i = 0; i < num_philosophers; i++){
		for(int j = 0; j < num_philosophers; j++)
			printf("%d ",r[i][j]);
		printf("\n");
	}
	printf("\n");
	fflush(stdout);
	sem_post(&sem_print);
}

// checks deadlock in the code.
void check_deadlock() {
	if(eating > 0) return;
	for (int i = 0; i < num_philosophers; ++i)
	{
		if(fork_status[i] == 1) return; // fork is free, hence no deadlock.
	}
	sleep(1);
	if(eating > 0) return;

	print_matrices();
	printf("Parent detects deadlock, going to initiate recovery.\n");
	fflush(stdout);

	int x = rand() % 5;
	printf("Parent preemts Philosopher %d\n", x);
	fflush(stdout);
	
	a[x][left(x)]=0;
	sem_post(&sem_forks[left(x)]);
	return;
}

// actual algorithm.
void *solve(void *args) {
	int philosopher_id = (int)args;
	int lt = left(philosopher_id);
	int rt = right(philosopher_id);

	while(1) {
		r[philosopher_id][lt] = r[philosopher_id][rt] = 0;
		printf("Philosopher %d starts thinking!\n", philosopher_id);
		fflush(stdout);	

		sleep(1);
		printf("Philosopher %d is feeling hungry\n", philosopher_id);
		fflush(stdout);
		
		printf("Philosopher %d requests for fork(left) %d\n", philosopher_id, lt);
		fflush(stdout);
		r[philosopher_id][lt]=1;
		print_matrices();
		
		sem_wait(&sem_forks[lt]);
			fork_status[lt]=0; // grab the fork.
			printf("Philosopher %d grabs fork(left) %d\n", philosopher_id, lt);
			fflush(stdout);
			r[philosopher_id][lt]=0;
			a[philosopher_id][lt]=1;
			print_matrices();

			sleep(1); // sleep for 1 sec before going for right fork.

			// when the parent preempts the thread.
			if(a[philosopher_id][lt] == 0) {
				continue;
			}

			printf("Philosopher %d requests for fork(right) %d\n", philosopher_id, rt);
			fflush(stdout);
			r[philosopher_id][rt]=1;

			sem_wait(&sem_forks[rt]);
				fork_status[rt]=0; // grab the fork.
				printf("Philosopher %d grabs fork %d (right)\n", philosopher_id, rt);
				fflush(stdout);
				r[philosopher_id][rt]=0;
				a[philosopher_id][rt]=1;

				printf("Philosopher %d starts eating\n", philosopher_id);
				fflush(stdout);
				eating++;
				sleep(1);

				printf("Philosopher %d ends eating and releases forks %d(left) and %d(right)\n", philosopher_id, lt, rt);
				fflush(stdout);
				fork_status[rt] = 1; // release the fork.
				a[philosopher_id][rt]=0;
				eating--;
			sem_post(&sem_forks[rt]);

			a[philosopher_id][lt]=0;
			fork_status[lt]=1; // drop the fork.
		sem_post(&sem_forks[lt]);
		break;
	}

	done[philosopher_id]=1;
	pthread_exit((void *)0);
}

int main(int argc, char const *argv[])
{
	// initialize semaphores.
	sem_init(&sem_allocation_resource, 0, 1);
	sem_init(&sem_print, 0, 1);

	for (int i = 0; i < num_philosophers; ++i)
	{
		sem_init(&sem_forks[i], 0, 1);
	}

	// set starting values.
	memset(fork_status, 1, sizeof(fork_status));
	memset(a, 0, sizeof(a));
	memset(r, 0, sizeof(r));
	memset(done, 0, sizeof(done));

	for (int i = 0; i < num_philosophers; ++i)
	{
		pthread_create(&thread_id[i], NULL, solve, (void *)i);
	}

	//Checks for deadlock
	while(1){
		check_deadlock();
		int alldone = 0;
		for (int i = 0; i < num_philosophers; ++i)
		{
			alldone += done[i];
		}

		if(alldone == 5) break;
	}

	//Thread joins.
	for(int i = 0; i < num_philosophers; i++)
		pthread_join(thread_id[i], NULL);

	sem_destroy(&sem_allocation_resource);
	sem_destroy(&sem_print);

	for (int i = 0; i < num_philosophers; ++i)
	{
		sem_destroy(&sem_forks[i]);
	}
	return 0;
}