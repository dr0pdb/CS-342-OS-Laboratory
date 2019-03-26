#include <stdlib.h>
#include <stdio.h>

#define MAX 100000
int work_queue[MAX], nextrequest=0, head_position=50, num_entries, total_head_movement=0;

int main(int argc, char const *argv[])
{
	printf("Enter the number of entries in the work queue: ");
	scanf("%d", &num_entries);
	printf("Enter the entries separated by space: ");
	for (int i = 0; i < num_entries; ++i)
	{
		scanf("%d", &work_queue[i]);
	}
	for(int i = 0; i < num_entries; ++i) {
		printf("Moving from position %d to %d\n", head_position, work_queue[i]);
		int current_movement = abs(work_queue[i] - head_position); // cost of this movement.
		total_head_movement += current_movement; // adding it to the total cost.
		head_position = work_queue[i]; // head now at the current cylinder
	}
	// print result.
	printf("The total head movement for satisfying this work queue is: %d\n", total_head_movement);
	printf("The total seek time for this is: %d ms\n", 5 * total_head_movement);
	return 0;
}