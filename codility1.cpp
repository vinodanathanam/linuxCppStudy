#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class comp:public binary_function<int, int, bool>{
public:
	comp(int val):a(val){}

	bool operator()(int K, int b) const
	{
		//printf("%d %d %d\n",K, a, b);
		return (K == (a + b));
	}

private:
	int a;
};

int findCompPairs(const vector<int> vec, int K)
{
	int retVal(0);
	
	vector<int>::const_iterator itr;
	
	for(itr = vec.begin(); itr != vec.end(); itr++){
		retVal += count_if(vec.begin(), vec.end(), bind1st(comp(*itr), K));
	}	

	return retVal;
}

int main(){
	vector<int> v;
	v.push_back(1); 
	v.push_back(8); 
	v.push_back(-3); 
	v.push_back(0); 
	v.push_back(1); 
	v.push_back(3); 
	v.push_back(-2); 
	v.push_back(4); 
	v.push_back(5); 
	
	
	for(int K = 1; K <= 10; K++)
	{
		int val  = findCompPairs(v, K);
		printf("Count of K's Comp of %d : %d\n",K, val); 
	}
	return 0;
}
