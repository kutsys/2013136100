#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
int run;  // ptest가 동작중이면 1, 없으면 0
char gpid[10]; // ptest의 프로세스 ID
void start(); // ptest 프로세스 시작 함수
void restart(); // ptest  프로세스 리스타트 함수
void pkill(); //ptest 프로세스 죽이는 함수
void print_command(); // 명령어 안내 출력

// ptest가 동작하는지 안하는지 검사하는 함수이다.
// 시그널 알람이 뜨면 호출되는 함수이다.
// 동작하면 ptest 프로세스 ID값을 읽어온다
void IsExist(int sig){

	if(sig == SIGALRM){
		FILE *fp = NULL;
	    	// 프로세스 ID값을 알아온다
	    	if((fp = popen("pgrep -x ptest","r")) ==NULL)
			     printf("error\n");

        // 프로스세 ID 값을 얻어온다
	    	if(fgets(gpid,10,fp) !=NULL){
			       printf("\n%s ",gpid);
			       run =1; // ID값이 있다는 것은 동작중이라는 뜻!
			      printf("running\n");
		    }
		      else // ID값이 없다면 동작 하지 않는다는 것
			printf("not existed\n");

	    pclose(fp);
	}
  // 다시 5초마다 알람
	alarm(5);

}

int main(){
	run = 0; // 처음 초기값을 0으로 일단 해둔다
	char input; // 사용자 명령어
  // 모니터링 을 5초마다 알람해둔다
        alarm(5);
	signal(SIGALRM,IsExist);
	
	print_command();
	while(1){
		scanf("%c",&input);

		switch(input){
			case 'q':
			case 'Q':
				pkill();
				printf("quit ! bye bye!\n\n");
				return 0;
			case 'k':
			case 'K':
				pkill();
				print_command();
				break;
			case 's':
			case 'S':
				start();
				print_command();
				break;
			case 'r':
			case 'R':
				restart();
				print_command();
				break;

		}

	}

}

void print_command(){
	puts("\n\n-----------------------------");
	puts("  Q : quit (quit pmon)   ");
	puts("  K : kill (kill ptest)      ");
	puts("  S : start (start ptest)    ");
	puts("  R : restart (restart ptest)");
	puts("-----------------------------");
}
// 프로세스 시작함수
void start(){
  // run 값에 따라서 판단...
  //run이 0이면 동작하지 않으므로 새로 시작...
  // run이 1이면 이미 동작중인 프로세스가 있음
	if(run == 0){
	        system("gnome-terminal --command \"./ptest\"");		
		run = 1;
	}
	else
		printf("already running\n\n");
}
// run이 0이면 start 함수 호출
// run이 1이면 동작 중인 프로세스를 pkill함수로 죽임
// 그리고 start 함수 호출
void restart(){
	if(run == 0){
		printf("newly started\n");
		start();
	}
	else{
		pkill();
		run = 0;
		printf("restartd!!\n\n");
		start();
	}
}

// 동작중이면 pkill 호출. SIGKILL 이용

void pkill(){
	if(run == 0)
		printf("not exist ptest \n\n");
	else{
    //프로세스 ID값을 정수로 변환
		kill(atoi(gpid), SIGKILL);
		run = 0;
		printf("Success killed ptest!!\n\n");
	}
}
