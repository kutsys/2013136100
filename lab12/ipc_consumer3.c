#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include "msgq.h"

int main(int argc, char* argv[]) {
	const char* studentName = "Lee Jinsol";
	char myPid[16];	
	char producerPid[MSGSIZE], studentId[MSGSIZE];
	Msgq msgBuf; 

	sprintf(myPid, "%d", getpid());

	//create new message queue
	int msgKey = msgget(KEYVAL, 0666 | IPC_CREAT);
	if(msgKey==-1) {
		perror("msgget failed\n");
		exit(EXIT_FAILURE);
	}

	while(1) {
		//Read code///////////////////////////////////////////////////
		//receive message queue with PRODUCER_PUSHED type
		msgrcv(msgKey, &msgBuf, sizeof(Msgq)-sizeof(long), PRODUCER_PUSHED, 0);
		//read producerPid from message queue
		strcpy(producerPid, msgBuf.msgTxt);
		//receive message queue with PRODUCER_PUSHED type
		msgrcv(msgKey, &msgBuf, sizeof(Msgq)-sizeof(long), PRODUCER_PUSHED, 0);
		//read studentId from message queue
		strcpy(studentId, msgBuf.msgTxt);

		//print gathered data
		printf("Producer PID: %s \nStudent ID: %s\n", producerPid, studentId);

		//Write code///////////////////////////////////////////////////////////////
		//set message type to CONSUMER_PUSHED
		msgBuf.msgType = CONSUMER_PUSHED;
		//write myPid into msgTxt
		strcpy(msgBuf.msgTxt, myPid);
		//send message
		msgsnd(msgKey, &msgBuf, sizeof(Msgq)-sizeof(long), 0);
		//set message type to CONSUMER_PUSHED
		msgBuf.msgType = CONSUMER_PUSHED;
		//write studentName into msgTxt
		strcpy(msgBuf.msgTxt, studentName);
		//send message
		msgsnd(msgKey, &msgBuf, sizeof(Msgq)-sizeof(long), 0);
	}
	exit(EXIT_SUCCESS);
}
