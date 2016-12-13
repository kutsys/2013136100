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
	const char* studentName = "Lee Jinsol";
	char myPid[16];	
	char producerPid[SOCSIZE], studentId[SOCSIZE];
	char buf[SOCSIZE];
	struct sockaddr_un serverAddress;

	sprintf(myPid, "%d", getpid());

	//create a socket for the client
	int mySocket = socket(AF_UNIX, SOCK_STREAM, 0);

	//name the socket as agreed with the server
	serverAddress.sun_family = AF_UNIX;
	strcpy(serverAddress.sun_path, LSOC);
	socklen_t len = sizeof(serverAddress);

	while(1) {
		//connect client socket to server socket
		int result = connect(mySocket,(struct sockaddr*)&serverAddress, len);
	
		//wait if connection fails
		if(result==-1) {
			sleep(0);
			continue;
		}

		//read producerPid/studentId from server
		read(mySocket, producerPid, SOCSIZE);
		read(mySocket, studentId, SOCSIZE);
		
		//print gathered data
		printf("Producer PID: %s \nStudent ID: %s\n", producerPid, studentId);

		//wrtie myPid/studentName into server via mySocket
		strcpy(buf, myPid);
		write(mySocket, buf, SOCSIZE);
		strcpy(buf, studentName);
		write(mySocket, buf, SOCSIZE);

		//close connection
		close(mySocket);
		
		//recreate client socket forrepeated operation
		mySocket = socket(AF_UNIX, SOCK_STREAM, 0);
	}
	exit(EXIT_SUCCESS);
}
