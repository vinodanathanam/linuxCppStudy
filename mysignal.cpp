#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void myhandler(int sig)
{
	printf("The signal fired is  %d\n",sig);
	signal(SIGINT, SIG_DFL);
}

int main(int argc, char* argv[])
{

	signal(SIGINT, myhandler);
	while(1)
	{
		printf("Hello there ! \n");
		sleep(1);
	}
	
	return 0;
}
