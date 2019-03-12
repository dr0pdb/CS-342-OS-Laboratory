#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

int numResources = 4;
int numProcesses = 5;

int available[1000] = {1,5,2,0};
int allocationMatrix[1000][1000] = {
	{0,0,1,2},
	{1,0,0,0},
	{1,3,5,4},
	{0,6,3,2},
	{0,0,1,4}
};
int maxDemand[1000][1000] = {
	{0,0,1,2},
	{1,7,5,0},
	{2,3,5,6},
	{0,6,5,2},
	{0,6,5,6}
};
int need[1000][1000];
int order[1000], order_index=0, finished[1000], counter=0;

int bankersAlgorithm() {
	// variables.
	int prevcounter = -1; counter=0; memset(finished, 0, sizeof(finished));
	available[0]=1; available[1]=5; available[2]=2; available[3]=0;

	while(counter < numProcesses && prevcounter != counter) {
		prevcounter = counter;
		for (int i = 0; i < numProcesses; ++i)
		{
			if(finished[i]) continue;
			int possible = 1;
			for (int j = 0; j < numResources; ++j)
			{
				// check if we can allocate the required resources for the process.
				if(need[i][j] > available[j]) {
					possible = 0;
					break;
				}
			}

			// if possible to allocate, then allocate.
			if(possible) {
				order[order_index] = i;
				order_index++;
				counter++;
				finished[i]=1;
				for (int j = 0; j < numResources; ++j)
				{
					available[j] += allocationMatrix[i][j];
				}
			}
		}
	}

	// return 0 if all the processes are finished(safe state).
	return (counter != numProcesses);
}

int main(int argc, char const *argv[])
{
	freopen ("input.txt","r",stdin);
	cin>>numProcesses>>numResources;

	// allocation.
	for (int i = 0; i < numProcesses; ++i)
	{
		for (int j = 0; j < numResources; ++j)
		{
			cin>>allocationMatrix[i][j];
		}
	}

	// max demand.
	for (int i = 0; i < numProcesses; ++i)
	{
		for (int j = 0; j < numResources; ++j)
		{
			cin>>maxDemand[i][j];
		}
	}

	//available.
	for (int i = 0; i < numResources; ++i)
	{
		cin>>available[i];
	}

	// finding the need matrix.
	printf("----------The Need Matrix--------\n");
	for (int i = 0; i < numProcesses; ++i)
	{
		for (int j = 0; j < numResources; ++j)
		{
			need[i][j] = maxDemand[i][j] - allocationMatrix[i][j];
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// check safe state.
	if(bankersAlgorithm()) {
		printf("The system is in unsafe state!!\nThese processes can't be executed safely: ");
		for (int i = 0; i < numProcesses; ++i)
		{
			if(!finished[i]) {
				printf("%d ", i);
			}
		}
	} else {
		printf("The system is in safe state!\nThe processes can be executed in this order: ");
		for (int i = 0; i < numProcesses; ++i)
		{
			printf("P%d ", order[i]);
		}
		printf("\n");
	}
	
	// checking if it's possible to allocate resources.
	printf("\n-------After a new demand of (0,4,2,0) from P1------\n");
	if(available[1] < 4 || available[2] < 2) {
		printf("No the demands cannot be met since the resources aren't available\n");
		return 0;
	}

	// allocating resources.
	allocationMatrix[1][1]+=4; allocationMatrix[1][2]+=2;
	available[1]-=4; available[2]-=2;

	printf("The Allocation Matrix\n");
	for (int i = 0; i < numProcesses; ++i)
	{
		for (int j = 0; j < numResources; ++j)
		{
			printf("%d ", allocationMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// checking for safety again.
	if (bankersAlgorithm())
	{
		printf("No the demands cannot be fulfilled immediately since it puts the system in unsafe state!\n");
	} else {
		printf("Yes we can safely fulfill the demands of P1!\nThe processes can be executed in this order: ");
		for (int i = 0; i < numProcesses; ++i)
		{
			printf("P%d ", order[i]);
		}
		printf("\n");
	}

	return 0;
}