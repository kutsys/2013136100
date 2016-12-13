#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define KEYVAL 0627
#define MEMSIZE 64
#define FFLAG 0
#define PFLAG 1
#define CFLAG 2

char* shm = NULL;
void shm_free(int sig) {
	if(shm!=NULL)
		shmdt(shm);
}

int main(int argc, char* argv[]) {
	const char* studentName = "Lee Jinsol";
	char myPid[16];	
	sprintf(myPid, "%d", getpid());
	char producerPid[MEMSIZE], studentId[MEMSIZE];
	int shmid = shmget(KEYVAL, MEMSIZE, 0666 | IPC_CREAT);
	if(shmid==-1) {
		perror("shmget failed\n");
		exit(EXIT_FAILURE);
	}
	shm = shmat(shmid, NULL, 0);
	if(shm == (char*)(-1)) {
		perror("shmat failed\n");
		exit(EXIT_FAILURE);
	}

	//free shared memory on conditions below
	(void) signal(SIGTERM, shm_free);
	(void) signal(SIGKILL, shm_free);
	(void) signal(SIGSTOP, shm_free);

	while(1) {
		//Read code/////////////////////////////////////////////////////////
		//procuder and consumer has same priority.
		//While shared memory flag is set to FFLAG/CFLAG,
		//put ipc_consumer into suspended state.
		//Meaning it won't access shared memory till
		//shm[0] is set to PFLAG.
		while(shm[0]!=PFLAG)
			sleep(0);

		//read producerPid from shared memory
		strncpy(producerPid, shm+1, MEMSIZE-1);
		//put consumer into suspended state, allowing producer to write new value
		shm[0] = FFLAG;
		while(shm[0]!=PFLAG)
			sleep(0);
		//read studentId from shared memory
		strncpy(studentId, shm+1, MEMSIZE-1);
		//set memory flag as FFLAG
		shm[0] = FFLAG;

		//print gathered data
		printf("Producer PID: %s \nStudent ID: %s\n", producerPid, studentId);

		//Write code/////////////////////////////////////////////////////////
		//write myPid into shared memory
		//this will put producer into suspended state
		strcpy(shm+1, myPid);
		//producer will read values from shared memory
		shm[0] = CFLAG;
		//wait till producer is ready to copy new value
		while(shm[0]!=FFLAG)
			sleep(0);
		//write studentName into shared memory
		strcpy(shm+1, studentName);
		//producer will read values from shared memory
		shm[0] = CFLAG;
	}
	exit(EXIT_SUCCESS);
}
