#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>

#define PRODUCER_FIFO "/tmp/prdc_fifo"
#define CONSUMER_FIFO "/tmp/csm_fifo"

int main(int argc, char* argv[]) {
	const char studentName[PIPE_BUF+1] = "Lee Jinsol";
	char myPid[PIPE_BUF+1], producerPid[PIPE_BUF+1], studentId[PIPE_BUF+1];	

	//put pid of current proccess into myPid variable
	sprintf(myPid, "%d", getpid());

	//check if CONSUMER_FIFO file exists
	if(access(CONSUMER_FIFO, F_OK)==-1) {
		int res = mkfifo(CONSUMER_FIFO, 0777);	//if not, create one
		if(res!=0) {
			printf("mkfifo failed.\n");
			exit(EXIT_FAILURE);
		}
	}

	int pipeId = -1;
	while(1) {
		//open producer pipe (Read Only)
		pipeId = open(PRODUCER_FIFO, O_RDONLY);

		//read producerPid, studentId from producer pipe
		read(pipeId, producerPid, PIPE_BUF);
		read(pipeId, studentId, PIPE_BUF);
		close(pipeId);

		//print gathered data
		printf("Producer PID: %s \nStudnet ID: %s\n", producerPid, studentId);

		//open consumer pipe (Write Only)
		pipeId = open(CONSUMER_FIFO, O_WRONLY);

		//write myPid, studentName into consumer pipe
		write(pipeId, myPid, PIPE_BUF);
		write(pipeId, studentName, PIPE_BUF);
		close(pipeId);
	}
	exit(EXIT_SUCCESS);
}
