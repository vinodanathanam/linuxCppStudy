#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int cutrod(const vector<int>& v, int n)
{
	if(n <= 0)
		return 0;

	int max = v[n];

	for(int i=1;i<n;i++)
	{
		int tmp = v[i] + cutrod(v, n-i);
		if(tmp > max)
			max = tmp;
	}
	
	return max;
}

int cutroddp(const vector<int>& v, int n)
{
	vector<int> res;
	res.reserve(10);
	res[0] = 0;
	
	for(int i = 1;i <= n; i++)
	{
		int max = v[i];
		
		for(int j = 1; j < i; j++)
		{
			int tmp = v[j] + res[i-j];
			if(tmp > max)
				max = tmp;
		}
		res[i] = max;
	}

	return res[n];
}

int main(int argc, char* argv[])
{
	vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(3);
	vec.push_back(10);
	vec.push_back(10);

	
	int m = cutroddp(vec, 10);
	
	printf("Cut rod val : %d\n",m);
	return 0;
}
