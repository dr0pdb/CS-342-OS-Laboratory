#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int fact(int a)
{
	if(a == 1)
		return 1;
	return a*fact(a-1);
}

int main(int argc,char* argv[])
{
	float a = atof(argv[1]); int b = atoi(argv[2]);
	printf("Child: (pid = %d) : ", getpid());
	
	float ans = 0; float temp = a;
	for(int i = 1 ; i < b ; i++)
	{
		ans += temp/(float)fact(i);
		temp = temp*a;
	}
	ans++;
	printf("For x = %.3f the first %d terms yields %f\n", a,b,ans);
}