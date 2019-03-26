#include <stdlib.h>
#include <stdio.h>

#define MAX 100000
int disk_requests[MAX], done[MAX]={0}, 
	current_head_position=50, num_entries,
	total_head_movement=0;

int comp (const void * p, const void * q) 
{
    int f = *((int*)p);
    int s = *((int*)q);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int main(int argc, char const *argv[])
{
	printf("Enter the number of disk requests: ");
	scanf("%d", &num_entries);
	printf("Enter the requests: ");
	for (int i = 0; i < num_entries; ++i)
	{
		scanf("%d", &disk_requests[i]);
	}
	printf("\n");

	// sorting the disk requests.
	qsort(disk_requests, num_entries, sizeof(int), comp);
	int ind = 0;
	while(ind < num_entries && disk_requests[ind] < current_head_position) {
		ind++;
	}

	// moving from position 50 till the end.
	for(int i = ind; i < num_entries; ++i) {
		printf("Moving from %d to %d\n", current_head_position, disk_requests[i]);
		int current_movement = abs(disk_requests[i] - current_head_position); // cost of this movement.
		total_head_movement += current_movement; // adding it to the total cost.
		current_head_position = disk_requests[i]; // head now at the current cylinder
		done[i] = 1;
	}

	// in c-scan, the disk moves to the end and then moves back to front without servicing any more requests.
	printf("Disk head moves to the end\n");
	total_head_movement += (199 - current_head_position);
	current_head_position = 199;
	printf("Disk moves back to the front\n");
	total_head_movement += 200;
	current_head_position = 0;

	// moving from start to end again.
	for (int i = 0; i < num_entries; ++i)
	{
		if(done[i]) continue;
		printf("Moving from %d to %d\n", current_head_position, disk_requests[i]);
		int current_movement = abs(disk_requests[i] - current_head_position);
		total_head_movement += current_movement; // add to total cost.
		current_head_position = disk_requests[i];
		done[i] = 1;
	}

	printf("The total head movement for satisfying this work queue is: %d\n", total_head_movement);
	printf("The total seek time for this is: %d ms\n", 5 * total_head_movement);
	return 0;
}