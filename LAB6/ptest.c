#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main() {
	struct tm *timeinfo;
	time_t t;
	FILE * fp;
	while(1) {
		time(&t); //epoch time
		timeinfo=localtime(&t);
		printf("%s", asctime(timeinfo));
		sleep(2);
	}
	
}

