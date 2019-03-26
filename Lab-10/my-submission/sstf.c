#include <stdlib.h>
#include <stdio.h>

#define MAX 100000
int work_queue[MAX], finished[MAX]={0}, nextrequest=0, head_position=50, num_entries, total_head_movement=0;

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
	int done_count=0;

	// Service requests in shortest seek time manner.
	while(done_count < num_entries) {
		int minimum_distance = __INT_MAX__;
		int minimum_service = 0;
		for (int i = 0; i < num_entries; ++i)
		{
			if(finished[i]) continue;
			if(abs(work_queue[i] - head_position) < minimum_distance) {
				minimum_distance = abs(work_queue[i] - head_position);
				minimum_service = i;
			}
		}

		printf("Moving from %d to %d\n", head_position, work_queue[minimum_service]);
		total_head_movement += minimum_distance;
		head_position = work_queue[minimum_service];
		done_count++;
		finished[minimum_service]=1;
	}

	// print result.
	printf("The total head movement for satisfying this work queue is: %d\n", total_head_movement);
	printf("The total seek time for this is: %d ms\n", 5 * total_head_movement);
	return 0;
}