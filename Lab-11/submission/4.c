#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

long long int M,L,P;

int main(){
	printf("Enter the value of M(GB), L(GB) and P(KB) separated by space: ");
	scanf("%lld %lld %lld", &M, &L, &P);
	M = M * (1LL << 30); // converting to words.
	L = L * (1LL << 30);
	P = P * (1LL << 10);

	long long int number_pages = L / P;
	long long int number_frames = M / P; // page size = frame size.
	long long m = __builtin_ctzll(M); // log2(M)
	long long l = __builtin_ctzll(L);
	long long p = __builtin_ctzll(P);
	long long page_table_size = l - p;
	printf("---Results---\n");
	printf("Number of pages: %lld\n", number_pages);
	printf("Number of frames: %lld\n", number_frames);
	printf("Number of bits to represent physical address space: %lld\n", m);
	printf("Number of bits to represent virtual address space: %lld\n", l);
	printf("Number of bits to represent page offset: %lld\n", p);
	printf("Page table size: %lld\n", page_table_size);

	return 0;
}
