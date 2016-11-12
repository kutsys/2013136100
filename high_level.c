#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define BUF_SIZE 512

int main(){

	char block[BUF_SIZE];
	FILE* in;
	FILE* out;
	int nread;
	

	in=fopen("very.avi", "r");
	out = fopen("highfile.out", "w");

	
	while((nread=fread(block, 1, BUF_SIZE, in))>0)
		printf(".\n");
		fwrite(block, 1, nread, out);
	sleep(5);
	

	fclose(in);
	fclose(out);
	exit(0);
}
