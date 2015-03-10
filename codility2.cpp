#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class triangle:public binary_function<int, int, bool>{
public:
	triangle(int aa):a(aa){}

	bool operator()(int b, int c) const
	{
		return ( a + b > c && 
			 b + c > a &&
			 c + a > b );
	}
private:
	int a;
};

int findtriangle(const vector<int> v){
	vector<int>::const_iterator itr1, itr2,itr3;

	bool found(false);
	for(itr1 = v.begin(); itr1 != v.end()-2 && found == false; itr1++){
		for(itr2 = itr1 + 1; itr2 != v.end()-1 && found == false; itr2++){
			itr3 = find_if(itr2+1, v.end(), bind1st(triangle(*itr1), *itr2 ));
			if(itr3 != v.end())
				found = true;
		}
	}

	return (found)?1:0;

}


int main(){
	vector<int> v;

/*	
	v.push_back(10);
	v.push_back(50);
	v.push_back(5);
	v.push_back(1);
*/
	v.push_back(10);
	v.push_back(2);
	v.push_back(5);
	v.push_back(1);
	v.push_back(8);
	v.push_back(20);
	
	int retval = findtriangle(v);
	printf("Find triangle returned %d\n",retval);	

	return 0;
}
