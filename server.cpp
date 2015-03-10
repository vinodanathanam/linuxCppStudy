#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>

#include <string.h>
#include <string>
using namespace std;

//#define NUMCONNECTIONS 1 

void* socketHandler(void*);

int main(int argc, char* argv[])
{
	int host_port = 5000;
	int maxConns(1);
	if(argc == 2)
	{
		maxConns = atoi(argv[1]);
	}
	int conns[maxConns];
	pthread_t threads[maxConns];
		
	struct sockaddr_in server, client;
	int hsock;

	/* Create socket */	
	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if(hsock == -1)
	{
		perror("Error initialising socket\n");
		exit(1);
	}
	

	/*Bind */
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(host_port);

	if(bind(hsock, (sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("Error calling Bind\n");
		exit(1);
	}

	/*Listen*/
	
	listen(hsock, maxConns);
	
	for(int j = 0; j < maxConns; j++)
	{
		conns[j] = 0;
		threads[j] = 0;
	}

	socklen_t ll = sizeof(struct sockaddr_in);	
	printf("Waiting for connections...\nMaximum connections allowed is %d\n", maxConns);
	printf("To support more connections use ./server [d] where d is number of max number of connections.\n");
	/*Accept*/
	int numConns(0);
	while(numConns < maxConns)
	{
		
		int conVal(0);
		if( (conVal = accept(hsock, (sockaddr*)&client, &ll)) != -1)
		{
			printf("Got connection from %s identifier supplied : %d \n", inet_ntoa(client.sin_addr),conVal);
			conns[numConns] = conVal;
			pthread_create(&threads[numConns], NULL, socketHandler, (void*)&conns[numConns]);
		}
		else
		{
			printf("Accept error. \n");
			break;
		}	

		numConns++;
		printf("Num of conn remaining : %d \n", maxConns-numConns);
	}	

	for(int i = 0; i < numConns; i++)
	{
		pthread_join(threads[i], NULL);
	}

	close(hsock);
	return 0;
}

void* socketHandler(void* param)
{
	int conn = *((int*)param);

	char buffer[1024];
	int buff_len = 1024;
	memset(buffer, '\0', buff_len);
	sprintf(buffer, "Connected.  id : %d\n", conn);
	send(conn, buffer, sizeof(buffer), 0);

	int bytecount(0);

	memset(buffer, '\0', buff_len);
	while(true)
	{
		memset(buffer, '\0', buff_len);	
		if(bytecount = recv(conn, buffer, buff_len, 0) == -1)
		{
			perror("Error receiving msg.\n");
			pthread_exit(0);
		}
		
		std::string buff(buffer);
		printf("%d : %s\n",conn, buff.c_str());
		
	
		if(buff == "exit")
		{
			memset(buffer, '\0', buff_len);
			strcpy(buffer, "Exiting ...");
			send(conn, buffer, sizeof(buffer),0);	
			break;
		}
		
		memset(buffer, '\0', buff_len);
		strcpy(buffer, "Server : ");
		strcat(buffer, buff.c_str());
		send(conn, buffer, sizeof(buffer),0);	
	
	}
	
	printf("Closing conn : %d\n", conn);
	close(conn);
	pthread_exit(0);
}

