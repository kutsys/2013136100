#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>

#define LSOC "/tmp/lsocket"
#define SOCSIZE 64

int main(int argc, char* argv[]) {
	const char* studentId = "2013136100";
	char myPid[16];	
	char consumerPid[SOCSIZE], studentName[SOCSIZE];
	char buf[SOCSIZE];
	struct sockaddr_un serverAddress;
	struct sockaddr_un clientAddress;

	sprintf(myPid, "%d", getpid());
	
	//remove any old socket
	unlink(LSOC);
	//create unnamed socket. Unix filesystem, Stream socket
	int mySocket = socket(AF_UNIX, SOCK_STREAM, 0);

	//name the socket
	serverAddress.sun_family = AF_UNIX;
	strcpy(serverAddress.sun_path, LSOC);
	socklen_t serverLen = sizeof(serverAddress);
	bind(mySocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	//create a connection queue and wait for clients
	listen(mySocket, 5);

	char cmdBuf[1024];
	while(1) {
		scanf("%s", cmdBuf);
		if(strcmp(cmdBuf, "start")==0) {
			//accept connection from client
			socklen_t clientLen = sizeof(clientAddress);
			int clientSocket = accept(mySocket, (struct sockaddr*)&clientAddress, &clientLen);

			//write myPid/studentID to client
			strcpy(buf, myPid);
			write(clientSocket, buf, SOCSIZE);
			strcpy(buf, studentId);
			write(clientSocket, buf, SOCSIZE);

			//read consumerPid/studentName from client	
			read(clientSocket, consumerPid, SOCSIZE);
			read(clientSocket, studentName, SOCSIZE);

			//close client connection
			close(clientSocket);

			//print gathered data
			printf("Producer PID: %s \nConsumer PID: %s \nStudent ID: %s \nStudent Name: %s\n", myPid, consumerPid, studentId, studentName);
		}
	}
	exit(EXIT_SUCCESS);
}
