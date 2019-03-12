#include <bits/stdc++.h>
using namespace std;

int fifo_output[500][500], lru_output[500][500];

int get_least_recent_page(int last_used_time[], int num_pages) {
	int minm = INT_MAX, mini = 0;
	for (int i = 0; i < num_pages; ++i)
	{
		if(last_used_time[i] < minm) {
			minm = last_used_time[i];
			mini = i;
		}
	}

	return mini;
}

int main(int argc, char const *argv[])
{
	freopen("pages.txt", "r", stdin);
	int num_pages, page_request;

	while(cin>>num_pages) {
		vector<int> input;

		memset(fifo_output, 0, sizeof(fifo_output));
		memset(lru_output, 0, sizeof(lru_output));

		int pages[num_pages], last_used_time[num_pages], start=0, occupied=0, fifo_faults=0, lru_faults=0;
		memset(pages, 0, sizeof(pages));

		while(cin>>page_request && page_request != -1) {
			input.push_back(page_request);
			bool found = false;
			int ind = input.size(); ind--;

			for (int i = 0; i < num_pages; ++i)
			{
				found |= (pages[i] == page_request);
			}

			if(!found) {
				fifo_faults++;
				pages[start] = page_request;
				start++; start %= num_pages;
				if (occupied < num_pages)
				{
					occupied++;
				}

				for(int j = 0; j < num_pages; j++) {
					fifo_output[ind][j] = pages[j];
				}
			} else {
				for(int j = 0; j < num_pages; j++) {
					fifo_output[ind][j] = -1;
				}
			}
		}

		cout<<"FIFO:\n";
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
				if(fifo_output[i][j] == -1) {
					cout<<"  ";
					continue;
				}
				cout<<fifo_output[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;

		memset(pages, 0, sizeof(pages));
		memset(last_used_time, -1, sizeof(last_used_time));

		start = 0; occupied = 0;
		for(int k = 0; k < input.size(); k++) {
			page_request = input[k];
			bool found = false;
			
			for (int i = 0; i < num_pages; ++i)
			{
				if(pages[i] == page_request) {
					found = true;
					last_used_time[i] = k;
					break;
				}
			}

			if(!found) {
				lru_faults++;
				int index = get_least_recent_page(last_used_time, num_pages);
				pages[index] = page_request;
				last_used_time[index] = k;
				if (occupied < num_pages)
				{
					occupied++;
				}

				for(int j = 0; j < num_pages; j++) {
					lru_output[k][j] = pages[j];
				}
			} else {
				for(int j = 0; j < num_pages; j++) {
					lru_output[k][j] = -1;
				}
			}
		}

		cout<<"LRU:\n";
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
				if(lru_output[i][j] == -1) {
					cout<<"  ";
					continue;
				}
				cout<<lru_output[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;

		cout<<"Using "<<num_pages<<" frames, the reference string yielded:\n";
		cout<<"Scheme\t#Faults\n";
		cout<<"FIFO\t"<<fifo_faults<<endl;
		cout<<"LRU\t"<<lru_faults<<endl<<endl;
	}

	return 0;
}
