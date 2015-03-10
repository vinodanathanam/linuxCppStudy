#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	char* days[7] = {"Sunday",
					"Monday",
					"Tuesday",
					"Wednesday",
					"Thursday",
					"Friday",
					"Saturday"};

	for(int i = 0; i < 7; i++){
		printf("days[%d] : %s\n", i, days[i]);
	}

	return 0;
}