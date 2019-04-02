#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int *disk;
int total_files = 0;

struct files{
	char name[50];
	int start;
	int blocks;
};

//this function checks if 'blocks' no of blocks are free in disk and store those indices in 'indices' array
int freespace(int *indices, int blocks, int start)
{
	int k = 1;
	indices[0] = start;

	// try random allocation first.
	for(int x = 0; x < 100; x++){
		if(k == blocks) // if space required is found, then return.
			return 1;
		int dup = 0;
		int i = rand() % 100;
		if(i != start && disk[i] == -10){
			for(int j = 0; j < k; j++)
				if(indices[j] == i)
					dup = 1;
			if(dup == 1)
				continue;
			indices[k++] = i;
		}
	}

	// if random allocation not successful, then try brute force.
	for(int i = 0; i < 100; i++){
		int dup = 0;
		if(k == blocks)
			return 1;
		if(i != start && disk[i] == -10){
			for(int j = 0; j < k; j++)
				if(indices[j] == i)
					dup = 1;
			if(dup == 1)
				continue;
			indices[k++] = i;
		}
	}
	return 0;
}

int main(){
	disk = malloc(100 * sizeof(int));
	for(int i = 0; i < 100; i++)
		disk[i] = -10;
	struct files file[100];
	while(1){
		printf("-----------------------------------------------\n");
		printf("1. Store New File\n2. Display Files Allocated\n3. Exit\n");
		printf("-----------------------------------------------\nChoose option: ");
		int option;
		scanf("%d", &option);

		if(option == 1){	
			printf("Enter File Name(No spaces in between): ");
			scanf("%s", file[total_files].name);
			printf("Enter number of blocks required: ");
			int b;
			scanf("%d", &b);
			printf("Enter starting index: ");
			int s;
			scanf("%d", &s);

			// start index is already in use.
			if(disk[s] != -10){
				printf("Start index not free\n\n");
				continue;
			}
			int *indices = malloc(b * sizeof(int)); // temporary array to get the free blocks.
			
			// check for space and allocate file if space available.
			if(freespace(indices, b, s)){
				file[total_files].start = s;
				file[total_files].blocks = b;
				for(int i = 0; i < b-1; i++)
					disk[indices[i]] = indices[i+1];
				disk[indices[b-1]] = -1;
				total_files++;
				printf("File Allocated\n\n");
			}
			else
				printf("%d free blocks not available in disk\n\n", b);
		} else if(option == 2){
			if(total_files == 0){
				printf("No files stored yet\n\n");
				continue;
			}
			printf("File\t\tBlocks\t\tStart\t\tIndices\n");
			for(int i = 0; i < total_files; i++){
				printf("%s\t\t%d\t\t%d\t\t%d", file[i].name, file[i].blocks, file[i].start, file[i].start);
				int next = file[i].start;
				for(int j = 0; j < file[i].blocks-1; j++){
					next = disk[next];
					printf("->%d", next);
				}
				printf("\n");
			}
			printf("\n");
		} else if(option == 3)
			break;
		else
			printf("Wrong Option Choosed.\n\n");
	}
	return 0;
}
