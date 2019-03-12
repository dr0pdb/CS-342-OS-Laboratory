#include <stdlib.h>
#include <stdio.h>

int global_variable = 1;

int main(int argc, char const *argv[]) {
	static int static_variable;
	int *heap_allocated_variable;
	int stack_allocated_variable;
	void *text_segment = &main;

	static_variable = 10;
	heap_allocated_variable = (int *) malloc(sizeof(int));
	*heap_allocated_variable = 50;
	stack_allocated_variable = 5;

	printf("Readability and Writability of various sections\n");

	printf("\nGlobal variables\n");
	printf("The address of the global_variable is %p and it's value is %d\n", &global_variable, global_variable);
	global_variable = 2;
	printf("Modified the global_variable and it's new value is %d\n", global_variable);
	printf("Hence global_variables can be read and written.\n");


	printf("\nStatic variables\n");
	printf("The address of the static_variable is %p and it's value is %d\n", &static_variable, static_variable);
	static_variable = 20;
	printf("Modified the static_variable and it's new value is %d\n", static_variable);
	printf("Hence static_variable can be read and written.\n");


	printf("\nHeap Allocated variables\n");
	printf("The address of the heap_allocated_variable is %p and it's value is %d\n", heap_allocated_variable, *heap_allocated_variable);
	*heap_allocated_variable = 100;
	printf("Modified the heap_allocated_variable and it's new value is %d\n", *heap_allocated_variable);
	printf("Hence heap_allocated_variable can be read and written.\n");

	
	printf("\nStack allocated variables\n");
	printf("The address of the stack_allocated_variable is %p and it's value is %d\n", &stack_allocated_variable, stack_allocated_variable);
	stack_allocated_variable = 20;
	printf("Modified the stack_allocated_variable and it's new value is %d\n", stack_allocated_variable);
	printf("Hence stack_allocated_variable can be read and written.\n");


	printf("\nText segment\n");
	printf("The address of the text segment variable is %p and it's value is %d\n", &text_segment, (int) text_segment);
	printf("The attempt to write the text_segment variable below will give segmentation fault which means that it is not writable.\n");
	fflush(stdout);
	*(int *) text_segment = 5;
	return 0;
}