#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

#define NUM_THREAD 10
#define NUM_REPEAT 20

int get_min();
void * thread_function(void * arg);

sem_t bin_sem;
int count[NUM_THREAD];

int main(){
	int res;
	int i;
	pthread_t a_thread[NUM_THREAD];
	void * thread_result;
	char ch_buf[20];

	// Semaphore initialization
	res = sem_init(&bin_sem, 0, 0);
		
	//initialize counter value for each thread
	for(i = 0; i<NUM_THREAD; i++){
		count[i] = 0;	
	}

	for(i = 0; i<NUM_THREAD; i++){
		res = pthread_create(&(a_thread[i]), NULL, thread_function, (void *)&i);
		if(res != 0){
			perror("Thread creation failed");
			exit(EXIT_FAILURE);	
		}	
		sleep(1);
	}

	//increase semaphore value by 1
	sem_post(&bin_sem);

	for(i = NUM_THREAD-1; i>=0; i--){
		res = pthread_join(a_thread[i], &thread_result);
		if(res == 0){
			printf("Thread joined\n");
		}
		else {
			perror("Thread join failed");
		}
	}
	printf("Finished Successfully\n");
	exit(EXIT_SUCCESS);	
}

//find thread with minimal counter value
int get_min(){
	int min = count[0];
	int i ;
	for(i=1; i<NUM_THREAD; i++){
		if( min > count[i]) min = count[i];
	}
	return min;
}

void * thread_function(void * arg){
	int thid = *(int *)arg;
	struct tm *ts;
	int r;
	time_t ltime;
	srand(time(NULL));

	//Synchronize thread using semaphore
	//If counter is same as lowest counter value amongest threads, go ahead and print.
	//Otherwise incrase semaphore value (Lock)
	while(1){	
		// bin_sem == 0 : blocked, wait for value to increase.
		// bin_sem > 0 : decrease by 1 and run thread
		sem_wait(&bin_sem);
		if(count[thid] == get_min()){
			r = rand()%10;
			ltime = time(NULL);
			ts = localtime(&ltime);

			printf("Thread: %d, Time: %d-%d-%d %d:%d:%d, Count: %d\n",thid,ts->tm_year+1900,ts->tm_mon+1,ts->tm_mday,ts->tm_hour,ts->tm_min,ts->tm_sec, ++count[thid]);

			//increase semaphore value by 1
			sem_post(&bin_sem);
			sleep(r);
		}
		else{	//if counter is higher than other threads, do not print
			//increase semaphore value by 1
			sem_post(&bin_sem);
			continue;
		}	//if counter reaches 20, terminate thread
		if(count[thid] == NUM_REPEAT) pthread_exit(NULL);
	}	
}
