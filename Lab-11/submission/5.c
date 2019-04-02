#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

long long M,N,L,n;
# define deb(x) printf("%lld\n", x);

int main(){
	printf("Enter the value of M(bits), N(in KB), L & n(space separated): \n");
	scanf("%lld %lld %lld %lld", &M, &N, &L, &n);
	long long page_size = N * (1LL << 10);
	long long frame_offset_bits = __builtin_ctzll(page_size);
	long long bits_to_address_a_frame = M - frame_offset_bits;
	long long page_table_entry_bits = __builtin_ctzll((long long)L);
	long long bits_for_n = __builtin_ctz(n);
	long long number_of_sets_in_cache = page_table_entry_bits - bits_for_n;
	long long bits_for_tag = bits_to_address_a_frame - number_of_sets_in_cache;
	printf("The bits needed for tag is: %lld\n", bits_for_tag);

	return 0;
}
