#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(int argc, char const *argv[])
{
	printf("Reading %s\n", argv[1]);
	FILE *fptr = fopen(argv[1], "r");
	if(fptr != NULL) {
		int cnt=0;
		char c = fgetc(fptr);
		while(c != EOF) {
			if(cnt%3 == 0) {
				printf(" %c", c);
				
			}
			cnt++;
			c = fgetc(fptr);
		}
	}

	return 0;
}