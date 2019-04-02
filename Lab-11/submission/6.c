#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int tlb_search_time, memory_access_time;
double hit_ratio;

int main(){
	printf("Enter the tlb search time, memory_access_time and hit_ratio(space separated): ");
	scanf("%d %d %lf", &tlb_search_time, &memory_access_time, &hit_ratio);
	double effective_memory_access = 
		(hit_ratio * (tlb_search_time + memory_access_time)) +
		((1 - hit_ratio) * (tlb_search_time + 2 * memory_access_time));
	printf("The effective_memory_access time is: %lfms\n", effective_memory_access);
	return 0;
}