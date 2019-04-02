#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int *disk;
char file_name[100][50];
int blocks_requested[100];
int start_index[100];
int total_files = 0;

//this function check if their are 'blocks' no of free blocks in disk from 'start' index
int freespace(int start, int blocks)
{
	for(int i = 0; i < blocks; i++)
		if(disk[start + i] == 1)
			return 0;
	return 1;
}

int main(){
	disk = calloc(100, sizeof(int));
	while(1){
		printf("-----------------------------------------------\n");
		printf("1. Store New File\n2. Display Files Allocated\n3. Exit\n");
		printf("-----------------------------------------------\nChoose option: ");
		int option;
		scanf("%d", &option);

		if(option == 1){
			printf("Enter File Name(No spaces in between): ");
			scanf("%s", file_name[total_files]);
			printf("Enter number of blocks required: ");
			int blocks;
			scanf("%d", &blocks);
			printf("Enter starting index: ");
			int start;
			scanf("%d", &start);

			//if free space is available then store the file.
			if(freespace(start, blocks)){
				start_index[total_files] = start;
				blocks_requested[total_files] = blocks;
				for(int i = 0; i < blocks; i++)
					disk[start+i] = 1;
				total_files++;
				printf("File Allocated\n\n");
			}
			else
				printf("%d free blocks not available at %d index\n\n", blocks, start);
		} else if(option == 2){
			if(total_files == 0){
				printf("No files stored yet\n\n");
				continue;
			}
			printf("File\t\tBlocks\t\tStart\n");
			for(int i = 0; i < total_files; i++)
				printf("%s\t\t%d\t\t%d\n", file_name[i], blocks_requested[i], start_index[i]);
			printf("\n");
		} else if(option == 3)
			break;
		else
			printf("Choose between 1 to 3.\n\n");
	}
	return 0;
}
