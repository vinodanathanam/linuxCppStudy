#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool isprime(long l)
{
	if((l % 2) == 0)
		return false;

	bool prime(true);
	long d = (long)sqrt(l);	

	for(long i=3; i <= d; i+=2)
	{
		if((l % i) == 0)
		{
			prime = false;
			break;
		}
	} 

	return prime;
}

long countprimes(long num)
{
	if(num <=1)
		return 0;

	long count(1);
	
	for(long i = 3; i < num; i+=2)
	{
		if(isprime(i))
			count++;
	}

	return count;
}


int main(int argc, char* argv[])
{

	if(argc != 2)
	{
		printf("Usage is ./prime [num] where num is the number which we use to find the prime numbers\n");
		return 1;
	}

	
	long num = atol(argv[1]);

	printf("Number of prime numbers below %ld is %ld\n",num, countprimes(num)); 

	return 0;
}
