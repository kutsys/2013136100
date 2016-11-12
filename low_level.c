#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define BUF_SIZE 1024

int main(){
	char block[BUF_SIZE];
	int in, out;
	int nread;
	time_t start, end;
	int dif;


	in = open("very.avi", O_RDONLY);
	out = open("lowfile.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

	printf("start\n");
	while((nread=read(in, block, BUF_SIZE))>0)
		printf(".\n");
		write(out, block, nread);
		sleep(5);
	printf("finish\n");

	

	close(in);
	close(out);
	exit(0);
}
