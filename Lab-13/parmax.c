#include <stdio.h> 
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define SIZE 1500

int l, r;
int arr[SIZE];

/*
	The printmax function to return the maximum.
*/
int printmax(){
	// if number of elements is less than or equal to 10.
	if(r - l + 1 <= 10){
		int maxm = -1;
		int i;
		for(i = l; i <= r; i++){
			if(maxm < arr[i])maxm = arr[i];
		}
		return maxm;
	}
	int m = (l + r)/2;
	pid_t pid = fork();
	if(!pid){
		r = m;
		int max = printmax();
		return max;
	}
	else{
		pid_t pid1 = fork();
		if(!pid1){
			l = m + 1;
			int max = printmax();
			return max;
		}
		else{
			int max1, max2;
			wait(&max1);
			wait(&max2);
			int max3;
			if(WEXITSTATUS(max1) > WEXITSTATUS(max2))max3 = WEXITSTATUS(max1);
			else max3 = WEXITSTATUS(max2);
			return max3;
		}
	}
}

int main(int argc, char** argv){
	// parsing the arguments.
	l = 0;
	r = atoi(argv[1]) - 1;
	srand(time(0));
	// generating and printing the array.
	printf("The array : ");
	for(int i = l; i <= r; i++){
		arr[i] = rand() % 128;
		printf("%d ", arr[i]);
	}
	printf("\n");

	// get the max value.
	int maxm = printmax();
	printf("The max value returned by process %d (%d -> %d) is: %d\n", getpid(), l, r, maxm);
	exit(maxm);
}