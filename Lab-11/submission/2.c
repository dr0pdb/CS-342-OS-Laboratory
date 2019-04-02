#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

long long int **disk;
int total_files = 0;

struct files{
	char name[50];
	int start;
	int blocks;
};

// checks if 'blocks' no of blocks are free in disk and store those indices in 'indices' array
int freespace(int *indices, int blocks, int start)
{
	int k = 0;
	// try random allocation first.
	for(int x = 0; x < 100; x++){
		int dup = 0;
		if(k == blocks)
			return 1;
		int i = rand() % 100;
		if(i != start && disk[i] == NULL){
			for(int j = 0; j < k; j++)
				if(indices[j] == i)
					dup = 1;
			if(dup == 1)
				continue;
			indices[k++] = i;		
		}
	}

	// if random allocation not successful try brute force.
	for(int i = 0; i < 100; i++) {
		if(k == blocks)
			return 1;
		int dup = 0;
		if(i != start && disk[i] == NULL){
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
	disk = malloc(100 * sizeof(long long int *));
	for(int i = 0; i < 100; i++)
		disk[i] = NULL;
	struct files file[100];
	while(1){
		printf("-----------------------------------------------\n");
		printf("1. Store New File\n2. Display Files Allocated\n3. Exit\n");
		printf("-----------------------------------------------\nChoose option: ");
		int option;
		scanf("%d", &option);

		//storing files
		if(option == 1){
			printf("Enter File Name(No spaces in between): ");
			scanf("%s", file[total_files].name);
			printf("Enter number of blocks required: ");
			int b;
			scanf("%d", &b);
			printf("Enter starting index: ");
			int s;
			scanf("%d", &s);
			if(disk[s] != NULL){
				printf("start index not free\n\n");
				continue;
			}
			int *indices = malloc(b * sizeof(int)); // temporary array to store indices.
			if(freespace(indices, b, s)){
				file[total_files].start = s;
				file[total_files].blocks = b;
				disk[s] = malloc(b * sizeof(long int));
				for(int i = 0; i < b; i++){
					disk[s][i] = indices[i];		//storing indices of file blocks in the starting index of file
					disk[indices[i]] = malloc(sizeof(long int));		
					disk[indices[i]][0] = 1;
				}
				total_files++;
				printf("File Allocated\n\n");
			}
			//lack of free space in the disk.
			else
				printf("%d free blocks not available in disk\n\n", b);
		}
		else if(option == 2){
			if(total_files == 0){
				printf("No files stored yet\n\n");
				continue;
			}
			printf("File\t\tBlocks\t\tStart\t\tIndices\n");
			for(int i = 0; i < total_files; i++){
				printf("%s\t\t%d\t\t%d\t\t", file[i].name, file[i].blocks, file[i].start);
				for(int j = 0; j < file[i].blocks; j++)				
					printf("%lld ", disk[file[i].start][j]);
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
