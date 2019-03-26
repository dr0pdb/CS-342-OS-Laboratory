#include <stdlib.h>
#include <stdio.h>

#define MAX 100000
int work_queue[MAX], finished[MAX]={0}, nextrequest=0, head_position=50, num_entries, total_head_movement=0;

int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int main(int argc, char const *argv[])
{
	printf("Enter the number of entries in the work queue: ");
	scanf("%d", &num_entries);
	printf("Enter the entries separated by space: ");
	for (int i = 0; i < num_entries; ++i)
	{
		scanf("%d", &work_queue[i]);
	}
	printf("\n");
	qsort(work_queue, num_entries, sizeof(int), comp);
	int ind = 0;
	while(ind < num_entries && work_queue[ind] < head_position) {
		ind++;
	}

	// moving from position 50 till the end.
	for(int i = ind; i < num_entries; ++i) {
		printf("Moving from %d to %d\n", head_position, work_queue[i]);
		int current_movement = abs(work_queue[i] - head_position); // cost of this movement.
		total_head_movement += current_movement; // adding it to the total cost.
		head_position = work_queue[i]; // head now at the current cylinder
		finished[i] = 1;
	}

	// in c-scan, the disk moves to the end and then moves back to front without servicing any more requests.
	printf("Disk head moves to the end\n");
	total_head_movement += (199 - head_position);
	head_position = 199;
	printf("Disk moves back to the front\n");
	total_head_movement += 200;
	head_position = 0;

	// moving from start to end again.
	for (int i = 0; i < num_entries; ++i)
	{
		if(finished[i]) continue;
		printf("Moving from %d to %d\n", head_position, work_queue[i]);
		int current_movement = abs(work_queue[i] - head_position); // cost of this movement.
		total_head_movement += current_movement; // adding it to the total cost.
		head_position = work_queue[i]; // head now at the current cylinder
		finished[i] = 1;
	}

	// print result.
	printf("The total head movement for satisfying this work queue is: %d\n", total_head_movement);
	printf("The total seek time for this is: %d ms\n", 5 * total_head_movement);
	return 0;
}