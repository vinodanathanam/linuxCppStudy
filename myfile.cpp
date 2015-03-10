#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <sys/time.h>



void readwritefile();
int getRndNumber(int limit);



int main(int argc, char* argv[])
{

	if(argc != 2)
	{
		printf("Error in usage. Try myfile [num] where num is the number of lines\n");
		exit(1);
	}

	long long num = atoll(argv[1]);
	int fd;
	fd = open("testfile.txt", O_CREAT | O_WRONLY, 0700);

	if(-1 == fd){
		printf("Error in create or open file.\n");
		exit(1);
	}


	char buff[10];
	memset(buff, '\0', 10);
	for(long long i = 0; i < num; i++)
	{
		int i1 = getRndNumber(100);
		int i2 = getRndNumber(100);

		memset(buff, '\0', 10);
		if(i1 < i2)
			sprintf(buff, "%d %d\n", i1, i2);
		else
			sprintf(buff, "%d %d\n", i2, i1);

		write(fd, buff, strlen(buff));
	}

	close(fd);
	printf("\n");
	return 0;
}



int getRndNumber(int limit){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_sec * tv.tv_usec);
	return rand() % limit;
}

void readwritefile()
{

	int fd;
	fd = open("testfile.txt", O_CREAT | O_WRONLY, 0700);

	if(-1 == fd){
		printf("Error in create or open file.\n");
		exit(1);
	}

	/*write*/
	char buff[256];
	strcpy(buff, "Hello world!\n");

	write(fd, buff, 13);

	close(fd);

	/*read*/

	char rbuff[256];
	fd = open("testfile.txt", O_RDONLY, 0700);

	if(-1 == fd){
		printf("Error in open file.\n");
		exit(1);
	}

	read(fd, rbuff, 13);
	rbuff[13] = '\0';

	close(fd);

	printf("Read buff : %s\n", rbuff);
}


