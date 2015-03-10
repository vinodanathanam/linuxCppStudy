#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

unsigned long long fib(int n, vector<unsigned long long>& v)
{
	if(n == 0 || n == 1)
	{
		if(v[n] == -1)
		{
			v[n] = n;
		}
		return v[n];
	}	

	if(v[n] == -1)
	{
		v[n] = fib(n-1, v) + fib(n-2, v);
	}

	return v[n];	
}


int main(int argc, char* argv[])
{

	if(argc != 2)
	{
		printf("USAGE is ./fib [num] where num is the number whose fib we need...\n");
		return 1;
	}

	int num = atoi(argv[1]);	

	vector<unsigned long long> res;
	res.reserve(100000);
	res.assign(100000, -1);

	printf("Fib of %d is : %llu\n",num, fib(num, res));	

	return 0;

}
