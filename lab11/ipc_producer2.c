#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define KEYVAL 0627
#define MEMSIZE 64
#define FFLAG 0
#define PFLAG 1
#define CFLAG 2

char* shm = NULL;

int main(int argc, char* argv[]) {
	const char* studentId = "2013136100";
	char myPid[16];	
	char consumerPid[MEMSIZE], studentName[MEMSIZE];
	sprintf(myPid, "%d", getpid());

	//request new shared memory space
	//IPC_CREAT : Create new shared memory if key value is new
	int shmid = shmget(KEYVAL, MEMSIZE, 0666 | IPC_CREAT);
	if(shmid==-1) {
		perror("shmget failed\n");
		exit(EXIT_FAILURE);
	}

	//attach process memory to shared memory
	shm = shmat(shmid, NULL, 0);
	if(shm == (char*)(-1)) {
		perror("shmat failed\n");
		exit(EXIT_FAILURE);
	}

	char cmdBuf[1024];
	while(1) {
		scanf("%s", cmdBuf);
		if(strcmp(cmdBuf, "start")==0) {
			//Write code///////////////////////////////////////////////////////////
			//write myPid into shared memory
			strcpy(shm+1, myPid);
			//put producer into suspended state, allowing consumer to read new value
			shm[0] = PFLAG;
			while(shm[0]!=FFLAG)
				sleep(0);
			//write studentId into shared memory
			strcpy(shm+1, studentId);
			//put producer into suspended state, allowing consumer to read new value
			shm[0] = PFLAG;

			//Read code///////////////////////////////////////////////////////////
			//wait till memory access is freed
			while(shm[0]!=CFLAG)
				sleep(0);
			//read consumerPid from shared memory
			strncpy(consumerPid, shm+1, MEMSIZE-1);
			//consumer will write new value to shared memory	
			shm[0] = FFLAG;
			//wait till memory access is freed
			while(shm[0]!=CFLAG)
				sleep(0);
			//read studentName from shared memory
			strncpy(studentName, shm+1, MEMSIZE-1);
			//memory freed. consumer will resume whole operation
			shm[0] = FFLAG;

			//print gathered data
			printf("Producer PID: %s \nConsumer PID: %s \nStudent ID: %s \nStudent Name: %s\n", myPid, consumerPid, studentId, studentName);
		}
	}
	exit(EXIT_SUCCESS);
}
