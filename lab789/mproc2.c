#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define TOTAL_THREAD 10

void* thread_function(void *arg) {
	int count = 0;
	int r;
	time_t ltime;
	struct tm *ts;



	while(1) {
		ltime = time(NULL);
		ts = localtime(&ltime);
		srand(ltime);
		
		printf("Thread: %d, Count : %d, ",(int)pthread_self() ,++count);
		printf("Local Time : %4d-%2d-%2d %2d:%2d:%2d\n", ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec);
		
		r = rand()%10;
		sleep(r);
		
		if(count == 20)
			pthread_exit(NULL);
	}
}

int main () {
	int res;
	pthread_t threads[TOTAL_THREAD];
	void *thread_result;

	printf("2009160118 Lee Dong-Seok\n");

	for(int i=0; i<TOTAL_THREAD; i++) {
		printf("Creating Thread.\n");
		res = pthread_create(&threads[i], NULL, thread_function, NULL);
		
		if(res != 0) {
			printf("Thread creation failed.\n");
			exit(EXIT_FAILURE);
		}
	}

	for(int i=0; i<TOTAL_THREAD; i++) {
		res = pthread_join(threads[i], &thread_result);
		
		if(res == 0) {
			printf("Thread Joined.\n");
		} else {
			printf("Thread join failed.\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("Finished (thread)\n");	
	exit(EXIT_SUCCESS);
}
