#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* thread_fn(void* p);

typedef struct tval{
	int num;
	char val;
	tval(char c, int rep):val(c),num(rep){}
}tparam;

int main(int argc, char* argv[])
{
	int num = 1;
	if(argc == 2){
		num = atoi(argv[1]);	
	}
	else{
		printf("Please Use the format ./pthread [n] where n is the number of times to loop\n");				
		return 1;
	}
	
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;

	tparam a('a',num);	
	pthread_create(&t1, NULL, thread_fn, (void*)&a);
	tparam b('b',num);	
	pthread_create(&t2, NULL, thread_fn, (void*)&b);
	tparam c('c',num);	
	pthread_create(&t3, NULL, thread_fn, (void*)&c);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	
	printf("\n");
	return 0;
}

void* thread_fn(void* p){
	tparam* c = (tparam*)p;
//	printf("%c",*c);
	for(int i = 0; i < c->num; i++){
		printf("%c ",c->val);
	}
}
