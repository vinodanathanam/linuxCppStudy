#include <iostream>
#include <boost/array.hpp>
#include <boost/tuple/tuple.hpp>
#include <string>

using namespace std;

int main(){

//	boost::array<int, 4> arr = {{1,2,3,4}};
//	cout<< "hi" << arr[0];
	
	typedef boost::tuple<std::string, std::string, int> person;
	person p = boost::make_tuple("Vinod", "Anathanam", 42);

	cout << boost::get<0>(p) << std::endl;
	cout << boost::get<1>(p) << std::endl;
	cout << boost::get<2>(p) << std::endl;

	return 0;
}
