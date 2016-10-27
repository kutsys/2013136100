#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h> //for using memset

pid_t pid = -1;

void PrintCommand() {
	printf("\nQ(quit) : quit pmon");
	printf("\nk(kill) : kill ptest");
	printf("\nS(start) : start ptest");
	printf("\nR(restart) : restart ptest");
}

void FindPro(char* pname) {
	FILE* pipe;
	char buf[1024];
	memset(buf, '\0', 50);
	pipe = popen("pgrep test$", "r");
	//after file open, order the find pid of ptest
	fgets(buf, 1024, pipe);
	//receive the pid from pipe
	if(buf[0] != '\0')
		pid=atoi(buf);
	else
		pid = -1;
	pclose(pipe);
}
