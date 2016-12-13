#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include "msgq.h"

int main(int argc, char* argv[]) {
	const char* studentId = "2013136100";
	char myPid[16];	
	char consumerPid[MSGSIZE], studentName[MSGSIZE];
	Msgq msgBuf; 

	sprintf(myPid, "%d", getpid());

	//create new message queue
	int msgKey = msgget(KEYVAL, 0666 | IPC_CREAT);
	if(msgKey==-1) {
		perror("msgget failed\n");
		exit(EXIT_FAILURE);
	}

	char cmdBuf[1024];
	while(1) {
		scanf("%s", cmdBuf);
		if(strcmp(cmdBuf, "start")==0) {
			//Write code/////////////////////////////////////////////////////
			//Set message type to PRODUCER_PUSHED
			msgBuf.msgType = PRODUCER_PUSHED;
			//write myPid into msgTxt
			strcpy(msgBuf.msgTxt, myPid);
			//send message
			msgsnd(msgKey, &msgBuf, sizeof(Msgq)-sizeof(long), 0);
			//Set message type to PRODUCER_PUSHED
			msgBuf.msgType = PRODUCER_PUSHED;
			//write studentId into msgTxt
			strcpy(msgBuf.msgTxt, studentId);
			//send message
			msgsnd(msgKey, &msgBuf, sizeof(Msgq)-sizeof(long), 0);

			//Read code/////////////////////////////////////////////////////
			//receive message queue with CONSUMER_PUSHED type
			msgrcv(msgKey, &msgBuf, sizeof(Msgq)-sizeof(long), CONSUMER_PUSHED, 0);
			//read consumerPid from message queue
			strcpy(consumerPid, msgBuf.msgTxt);
			//receive message queue with CONSUMER_PUSHED type
			msgrcv(msgKey, &msgBuf, sizeof(Msgq)-sizeof(long), CONSUMER_PUSHED, 0);
			//read studentName from message queue
			strcpy(studentName, msgBuf.msgTxt);
			
			//print gathered data
			printf("Producer PID: %s \nConsumer PID: %s \nStudent ID: %s \nStudent Name: %s\n", myPid, consumerPid, studentId, studentName);
		}
	}
	exit(EXIT_SUCCESS);
}
