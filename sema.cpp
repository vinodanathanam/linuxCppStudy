#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


void* fun1(void* ptr);
void* fun2(void* ptr);

char buff[256];
sem_t mutex;

int main(){

	printf("In main \n");
	
	char msg1[] = "Thread 1";
	char msg2[] = "Thread 2";

	pthread_t t1;
	pthread_t t2;

	sem_init(&mutex,0,1);

	pthread_create(&t1, NULL, fun1, (void*)msg1);
	pthread_create(&t2, NULL, fun2, (void*)msg2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);	

	sem_destroy(&mutex);

	return 0;
}

void* fun1(void* ptr)
{
	char* msg = (char*)ptr;
	
	sem_wait(&mutex);
	sprintf(buff, "%s", msg);
	sem_post(&mutex);
	//printf("%s\n",msg);
	pthread_exit(0);
}

void* fun2(void* ptr)
{
	sem_wait(&mutex);
	printf("%s\n",buff);
	sem_post(&mutex);

	pthread_exit(0);
}

