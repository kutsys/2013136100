#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

#define EXECTO 10
pid_t childPid[EXECTO];
void killChild(int sig) {
	printf("Terminated.\n");
        int i=0;
	for(i=0; i<EXECTO; ++i)
		kill(childPid[i], SIGTERM);
	exit(0);
}
int main(int argc, char* argv[]) {
	printf("Lab7_2013136100_Lee Jinsol\n");
	(void) signal(SIGTERM, killChild);
	srand(time(NULL));
	char seed[15];
	pid_t pid;
        int p=0;
	for(p=0; p<EXECTO; ++p) {
		pid = fork();
		rand();
		if(pid==0) {
			sprintf(seed, "%d", rand());
			execl("./subproc", "subproc", "20", "10", seed, NULL);
		}
		else
			childPid[p] = pid;
	}
	int state_val;
        int pp=0;
	for(pp=0; pp<EXECTO; ++pp)
		wait(&state_val);
	printf("Finished (process)\n");
	exit(0);
}
