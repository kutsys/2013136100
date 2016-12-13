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
	const char studentId[PIPE_BUF+1] = "2013136100";
	char myPid[PIPE_BUF+1], consumerPid[PIPE_BUF+1], studentName[PIPE_BUF+1];	

	//put pid of current proccess into myPid variable
	sprintf(myPid, "%d", getpid());
	
	//check if PRODUCER_FIFO file exists
	if(access(PRODUCER_FIFO, F_OK)==-1) {
		int res = mkfifo(PRODUCER_FIFO, 0777);	//if not, create one
		if(res!=0) {
			printf("mkfifo failed.\n");
			exit(EXIT_FAILURE);
		}
	}

	char cmdBuffer[1024];
	int pipeId;
	while(1) {
		scanf("%s", cmdBuffer);
		if(strcmp(cmdBuffer, "start")==0) {
			//open producer pipe (Write Only)
			pipeId = open(PRODUCER_FIFO, O_WRONLY);

			//write myPid, studentId into producer pipe
			write(pipeId, myPid, PIPE_BUF);
			write(pipeId, studentId, PIPE_BUF);
			close(pipeId);

			//open consumer pipe (Read Only)
			pipeId = open(CONSUMER_FIFO, O_RDONLY);

			//read consumerPid, studentName from consumer pipe
			read(pipeId, consumerPid, PIPE_BUF);
			read(pipeId, studentName, PIPE_BUF);
			close(pipeId);

			//print gathered data
			printf("Producer PID: %s \nConsumer PID: %s \nStudent ID: %s \nStudent Name: %s\n", myPid, consumerPid, studentId, studentName);
		}
	}
	exit(EXIT_SUCCESS);
}
