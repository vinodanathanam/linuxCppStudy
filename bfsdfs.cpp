#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <set>
#include <list>
using namespace std;

typedef vector< set<int> > vecset;

vecset m_vals;

void initialise();
void addvertices(int s, int v);
void BFS(int start);
void DFS(int start);

int main(){
	initialise();
	
	printf("BFS Search.............\n");
	for(int i = 1; i <= 10; i++){
		BFS(i);
	}	

	printf("DFS Search.............\n");
	for(int i = 1; i <= 10; i++){
		DFS(i);
	}	

	return 0;
}

void BFS(int start){
//go to a node and print val
//mark as visited
//add to Q

	vector<int> visited;
	visited.assign(10,0);
	
	list<int> Q;

	if(true == m_vals[start].empty()){
		return;
	}
	else{
		printf("%d ",start);
		visited[start] = 1;
		Q.push_front(start);
	}

	while(false == Q.empty()){
		int val = Q.front();
		Q.pop_front();

		set<int> vals = m_vals[val];
		set<int>::iterator itr;
		for(itr = vals.begin(); itr != vals.end(); itr++){
			if(0 == visited[*itr]){
				printf("%d ", *itr);
				visited[*itr] = 1;
				Q.push_back(*itr);
			}
		}
	}
	printf("\n");
}


void DFS(int start){
//go to a node and print val
//mark as visited
//add to stack

	vector<int> visited;
	visited.assign(10,0);
	
	list<int> mystack;

	if(true == m_vals[start].empty()){
		return;
	}
	else{
		printf("%d ",start);
		visited[start] = 1;
		mystack.push_front(start);
	}

	while(false == mystack.empty()){

		int val = mystack.front();	
		set<int> vals = m_vals[val];
		set<int>::iterator itr;
		bool allvisited(true);

		for(itr = vals.begin(); itr != vals.end(); itr++){
			if(0 == visited[*itr]){
				printf("%d ",*itr);
				visited[*itr] = 1;
				mystack.push_front(*itr);
				allvisited = false;
				break;
			}
		}		
		
		if(true == allvisited){
			mystack.pop_front();
		}
	}
	
	printf("\n");
}


void initialise(){
	m_vals.reserve(11);
	
	for(int i = 0; i < 11; i++){
		set<int> temp;
		m_vals.push_back(temp);
	}
	
	addvertices(1,2);
	addvertices(1,3);
	addvertices(2,4);
	addvertices(2,1);
	addvertices(3,1);
	addvertices(3,4);
	addvertices(3,6);
	addvertices(4,7);
	addvertices(4,3);
	addvertices(5,6);
	addvertices(5,7);
	addvertices(6,3);
	addvertices(6,5);
	addvertices(7,5);
	addvertices(7,4);
}

void addvertices(int s, int v){
	m_vals[s].insert(v);
}
