#include <stdlib.h>
#include <stdio.h>

#define MAXM 100000
int disk_requests[MAXM], done[MAXM]={0},
	nextrequest=0, current_head_position=50, 
	total_entries, total_head_movement=0;

// comparator for sorting the disk requests.
int sort_comparator (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int main(int argc, char const *argv[])
{
	printf("Enter the number of requests: ");
	scanf("%d", &total_entries);
	printf("Enter the requests separated by space: ");
	for (int i = 0; i < total_entries; ++i)
	{
		scanf("%d", &disk_requests[i]);
	}
	printf("\n");

	// sort the requests.
	qsort(disk_requests, total_entries, sizeof(int), sort_comparator);
	int ind = 0;
	while(ind < total_entries && disk_requests[ind] < current_head_position) {
		ind++;
	}

	// moving from position 50 till the end.
	for(int i = ind; i < total_entries; ++i) {
		printf("Moving from %d to %d\n", current_head_position, disk_requests[i]);
		int current_movement = abs(disk_requests[i] - current_head_position);
		total_head_movement += current_movement;
		current_head_position = disk_requests[i];
		done[i] = 1;
	}
	printf("Disk head moves to the end\n");
	total_head_movement += (199 - current_head_position);
	current_head_position = 199;

	// moving from the end to front.
	for (int i = total_entries-1; i >= 0; --i)
	{
		if(done[i]) continue;
		printf("Moving from %d to %d\n", current_head_position, disk_requests[i]);
		int current_movement = abs(disk_requests[i] - current_head_position);
		current_head_position = disk_requests[i];
		done[i] = 1;
	}

	// print result.
	printf("The total head movement for satisfying this work queue is: %d\n", total_head_movement);
	printf("The total seek time for this is: %d ms\n", 5 * total_head_movement);
	return 0;
}