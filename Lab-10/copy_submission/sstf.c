#include <stdlib.h>
#include <stdio.h>

#define MAXM 100000
int disk_requests[MAXM], done[MAXM]={0},
	nextrequest=0, current_head_position=50, 
	total_entries, total_head_movement=0;

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
	int done_count=0;

	// Service requests using sstf.
	while(done_count < total_entries) {
		int minimum_distance = __INT_MAX__;
		int minimum_service = 0;

		// find the request with minimum seek time requirement.
		for (int i = 0; i < total_entries; ++i)
		{
			if(done[i]) continue;
			if(abs(disk_requests[i] - current_head_position) < minimum_distance) {
				minimum_distance = abs(disk_requests[i] - current_head_position);
				minimum_service = i;
			}
		}

		// move from current position to the request with minimum seek requirments.
		printf("Moving from %d to %d\n", current_head_position, disk_requests[minimum_service]);
		total_head_movement += minimum_distance;
		current_head_position = disk_requests[minimum_service];
		done_count++;
		done[minimum_service]=1;
	}

	printf("The total head movement is: %d\n", total_head_movement);
	printf("The total seek time is: %d ms\n", 5 * total_head_movement);
	return 0;
}