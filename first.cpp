#include <stdio.h>
#include <stdlib.h>

#include <boost/tuple/tuple.hpp>
using namespace std;


//quicksort
void swap(int& l, int& r){
	int temp = l;
	l = r;
	r = temp;
}

int partition(int* arr, int l, int r){
	int x = arr[r];
	int i = l-1;

	for(int j = l; j < r; j++){
		if(arr[j] < x){
			i++;
			swap(arr[i], arr[j]);	
		}
	}
	
	swap(arr[++i], arr[r]);
	return i;
}

void quicksort(int* arr, int l, int r){
	if(l < r){
		int p = partition(arr, l, r);
		quicksort(arr, l, p-1);
		quicksort(arr, p+1, r);
	}	
}

//heapsort

int left(int index){
	return (2* index) + 1;
}

int right(int index){
	return (2 * index) + 2;
}

void maxheapify(int* arr, int index, int heapsize){
	int ll = left(index);
	int rr = right(index);
	int largest(index);

	if(ll <= heapsize && arr[ll] > arr[index]){
		largest = ll;
	}
	
	if(rr <= heapsize && arr[rr] > arr[largest]){
		largest = rr;
	}

	if(index != largest){
		swap(arr[index], arr[largest]);
		maxheapify(arr, largest, heapsize);
	}
}

void buildMaxHeap(int* arr, int l, int r, int heapsize){
	int mid = (l + r)/2;
	for(int i = mid; i >= 0; i--){
		maxheapify(arr, i, heapsize);
	}
}

void heapsort(int* arr, int l, int r, int heapsize){
	buildMaxHeap(arr, l, r, heapsize);
	int size(heapsize);
	
	for(int i = 0; i <= heapsize; i++){
		swap(arr[0], arr[size--]);
		maxheapify(arr, 0, size);
	}	
}

//maxsubarray
typedef boost::tuple<int , int , int > tpl;

tpl maxcrossarray(int* arr, int l, int mid, int r){
	int lsum = -99999, rsum = -99999;
	int sum(0);
	int ll(0), rr(0);
		
	for(int i = mid; i >= l; i--){
		sum += arr[i];
		if(sum > lsum){
			lsum = sum;
			ll = i;
		}
	}
	
	sum = 0;
	for(int j = mid+1; j <= r; j++){
		sum += arr[j];
		if(sum > rsum){
			rsum = sum;
			rr = j;
		}
	}

	return boost::make_tuple(ll, rr, lsum+rsum);

}


tpl maxsubarray(int* arr, int l , int r){
	if(l == r){
		return boost::make_tuple(l,r,l);
	}
	else{
		int mid = (l + r)/2;
		tpl ltpl = maxsubarray(arr, l, mid);
		tpl rtpl = maxsubarray(arr, mid+1, r);
		tpl ctpl = maxcrossarray(arr, l, mid, r);
		
		if(boost::get<2>(ltpl) > boost::get<2>(rtpl) && boost::get<2>(ltpl) > boost::get<2>(ctpl)){
			return ltpl;
		}
		else if (boost::get<2>(rtpl) > boost::get<2>(ltpl) && boost::get<2>(rtpl) > boost::get<2>(ctpl)){
			return rtpl;
		}
		else{
			return ctpl;
		}	
	}	
}

void revprint(char* str){
	char c = *str;
	if(c != '\0'){
		revprint(++str);
		printf("%c",c);
	}
}

int  main()
{
	char msg[] = "Hello World";
	printf("\nReverse print of %s is ",msg);
	revprint(msg);
	printf("\n\nArray Input\n");
	
	int arr1[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	int arr2[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	int arr3[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	int l, r;
	l = 0;
	r = 15;
	for(int i = l; i <= r; i++){
		printf("%d ",arr1[i]);
	}

	printf("\n\nQuick Sort.....\n");
	quicksort(arr1, l, r);
	
	for(int i = l; i <= r; i++){
		printf("%d ",arr1[i]);
	}
	
	printf("\n\nHeap Sort..........\n");
	heapsort(arr2, l, r, r);

	for(int i = l; i <= r; i++){
		printf("%d ",arr2[i]);
	}
	
	printf("\n\nMax subarray...........\n");
	tpl t = maxsubarray(arr3, l, r);
	printf("Left Index  : %d\nRight Index : %d\nSum	    : %d",boost::get<0>(t), boost::get<1>(t), boost::get<2>(t));
	
	printf("\n");

	
	return 0;
}
