#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <resolv.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;


int main(int argc, char* argv[])
{

        int host_port = 5000;
	char host_name[] = "localhost";

	struct hostent *hp;
        struct sockaddr_in server;
        int hsock;

        /* Create socket */
        hsock = socket(AF_INET, SOCK_STREAM, 0);
        if(hsock == -1)
        {
                perror("Error initialising socket\n");
                exit(1);
        }

	hp = gethostbyname(host_name);
        server.sin_family = AF_INET;
        //server.sin_addr.s_addr = inet_addr(host_name);
        server.sin_port = htons(host_port);

	memcpy(&server.sin_addr.s_addr, hp->h_addr, hp->h_length);

	if(connect(hsock, (struct sockaddr*)&server, sizeof(server)) == -1)
	{
		printf("Failed to connect to server\n");
		exit(1);	
	}

	char buffer[1024];
	int buff_len = 1024;
	int bytecount(0);
	if( (bytecount = recv(hsock, buffer, buff_len, 0)) == -1)
	{
		printf("Error while getting response\n");
	
		exit(1);
	}

	printf("%s\n", buffer);
	bool bcontinue = true;
	memset(buffer, '\0', buff_len);

	do
	{
		memset(buffer, '\0', buff_len);
		printf("Enter text to sent to server \n");
		fgets(buffer, 1024, stdin);
		buffer[strlen(buffer)-1] = '\0';
		if(strcmp(buffer, "exit") == 0)
			bcontinue = false;

		if( (bytecount = send(hsock, buffer, strlen(buffer), 0)) == -1)
		{
			printf("Error sending message \n");
			exit(1);
		}

		memset(buffer, '\0', buff_len);
		if( (bytecount = recv(hsock, buffer, buff_len, 0)) == -1)
		{
			printf("Error while getting response\n");
		
			exit(1);
		}

		printf("%s\n", buffer);
	}while(bcontinue == true);

	close(hsock);	
	return 0;
}
