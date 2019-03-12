#include <bits/stdc++.h>
using namespace std;

int lfu_output[500][500], optimal_output[500][500];

// returns the least frequent page to remove for lfu algorithm.
int get_least_frequent_page(int pages[], int frequency_pages[], int fifo_value[], int num_pages) {
	for (int i = 0; i < num_pages; ++i)
	{
		if(pages[i] == 0) {
			return i;
		}
	}

	int minm_value=frequency_pages[pages[0]], minm_index=0;

	for (int i = 1; i < num_pages; ++i)
	{
		if(minm_value > frequency_pages[pages[i]] 
			|| (minm_value == frequency_pages[pages[i]] && fifo_value[pages[minm_index]] > fifo_value[pages[i]])) {
			minm_value = frequency_pages[pages[i]];
			minm_index = i;
		}
	}

	frequency_pages[pages[minm_index]]=0;
	return minm_index;
}

// returns the optimal page to remove.
int get_optimal_victim(int pages[], int num_pages, int next_usage[]) {
	for (int i = 0; i < num_pages; ++i)
	{
		if(pages[i] == 0) {
			return i;
		}
	}

	int minm_index = 0;
	for (int i = 1; i < num_pages; ++i)
	{
		if(next_usage[pages[i]] > next_usage[pages[minm_index]]) {
			minm_index = i;
		}
	}

	return minm_index;
}

int main(int argc, char const *argv[])
{
	freopen("pages.txt", "r", stdin);
	int num_pages, page_request;

	while(cin>>num_pages) {
		vector<int> input;

		memset(lfu_output, 0, sizeof(lfu_output));
		memset(optimal_output, 0, sizeof(optimal_output));

		int pages[num_pages], frequency_pages[105], fifo_value[105], lfu_faults=0, optimal_faults=0;
		
		memset(pages, 0, sizeof(pages));
		memset(frequency_pages, 0, sizeof(frequency_pages));
		memset(fifo_value, -1, sizeof(fifo_value));

		while(cin>>page_request && page_request != -1) {
			input.push_back(page_request);
			bool found = false;
			int ind = input.size(); ind--;

			for (int i = 0; i < num_pages; ++i)
			{
				found |= (pages[i] == page_request);
			}

			if(!found) {
				lfu_faults++;

				int position = get_least_frequent_page(pages, frequency_pages, fifo_value, num_pages);
				pages[position] = page_request;

				for(int j = 0; j < num_pages; j++) {
					lfu_output[ind][j] = pages[j];
				}

				fifo_value[page_request]=ind;
			} else {
				for(int j = 0; j < num_pages; j++) {
					lfu_output[ind][j] = -1;
				}
			}

			// increment the frequency of the current requested page.
			frequency_pages[page_request]++;
		}

		// print the solution for lfu.
		cout<<"LFU:\n";
		for(int request: input) {
			cout<<request<<" ";
		}
		cout<<endl<<endl;
		for (int i = 0; i < 35; ++i)
		{
			cout<<"-";
		}
		cout<<endl;
		for (int j = 0; j < num_pages; ++j)
		{
			for (int i = 0; i < input.size(); ++i)
			{
				if(lfu_output[i][j] == -1) {
					cout<<"  ";
					continue;
				}
				cout<<lfu_output[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;

/*
	Solution for optimal case.
*/
		memset(pages, 0, sizeof(pages));
		int next_usage[105];
		for (int i = 0; i < 105; ++i)
		{
			next_usage[i] = 105;
			for (int j = 0; j < input.size(); ++j)
			{
				if(input[j] == i) {
					next_usage[i] = j;
					break;
				}
			}
		}

		for(int k = 0; k < input.size(); k++) {
			page_request = input[k];
			bool found = false;
			
			for (int i = 0; i < num_pages; ++i)
			{
				if(pages[i] == page_request) {
					found = true;
					break;
				}
			}

			if(!found) {
				optimal_faults++;
				int index = get_optimal_victim(pages, num_pages, next_usage);
				pages[index] = page_request;

				for(int j = 0; j < num_pages; j++) {
					optimal_output[k][j] = pages[j];
				}
			} else {
				for(int j = 0; j < num_pages; j++) {
					optimal_output[k][j] = -1;
				}
			}

			// update next usage of the page requested.
			next_usage[page_request] = 105;
			for (int l = k+1; l < input.size(); ++l)
			{
				if(input[l] == page_request) {
					next_usage[page_request] = l;
					break;
				}
			}
		}

		// printing for optimal case.
		cout<<"Optimal:\n";
		for(int request: input) {
			cout<<request<<" ";
		}
		cout<<endl<<endl;
		for (int i = 0; i < 35; ++i)
		{
			cout<<"-";
		}
		cout<<endl;
		for (int j = 0; j < num_pages; ++j)
		{
			for (int i = 0; i < input.size(); ++i)
			{
				if(optimal_output[i][j] == -1) {
					cout<<"  ";
					continue;
				}
				cout<<optimal_output[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;

		cout<<"Using "<<num_pages<<" frames, the reference string yielded:\n";
		cout<<"Scheme\t#Faults\n";
		cout<<"LFU\t"<<lfu_faults<<endl;
		cout<<"Optimal\t"<<optimal_faults<<endl<<endl;
	}



	return 0;
}
