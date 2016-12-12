#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
 
void monitor(int sig);
int get_pid();
void print_command();
void test_start();
void test_kill();
 
int main(){
	char command[2];
	int  work = 1;
	signal( SIGALRM, monitor);
	alarm(4);	
 
	while(work){//선택 
	print_command();
	scanf("%s", command);
	switch(command[0]){
	//testmon 종료
	case 'q':
	case 'Q':{ work = 0; break; }
	//test 죽이기
	case 'k':
	case 'K':{
	if( get_pid() )
	test_kill();	
	else 
	printf("test is not working!\n");
	
	break;
	}
	//test 시작
	case 's':
	case 'S':{
	if(get_pid())  //이미 시작되었을 경우
	printf("already executed!\n");
	else{
	test_start();
	printf("test start!\n");
	}	
	break;
	}
	//test 재시작
	case 'r':
	case 'R':{
	if( get_pid() ){ //test를 죽인 뒤 2초 후 다시 시작
	test_kill();
	alarm(2);
	test_start();
	printf("test restarted!\n");
	}
	else
	printf("test is not working!\n");
	break;
	}
	}	
	printf("\n\n");
	}
	
	return 0;
}
 
//test 실행여부 확인
void monitor(int sig){
	if(!get_pid()){//test가 실행되고 있지 않을 경우
	printf("test is terminated.\n");
	//test_start();	
	}
	else{ //test실행 확인, command 입력
	system("pgrep -x test");
	puts(">> operator's command: ");
	}
	alarm(4);
}
 
 //pid얻어오기
int get_pid(){
	FILE* read_pid;
	char context[1024];
	
	context[0] = '\0';
	read_pid = popen("pgrep -x test", "r");
	fread(context, 1, 1024, read_pid);
	pclose(read_pid);
 
	return atoi(context);	// test not working -> 0
}
 
//coommand 출력
void print_command(){
	puts("-----------------------------");
	puts("  Q : quit (quit testmon)   ");
	puts("  K : kill (kill test)      ");
	puts("  S : start (start test)    ");
	puts("  R : restart (restart test)");
	puts("-----------------------------");
}
 
//test 시작
void test_start(){
	system("./test  >> /dev/pts/25 &");	//test를 실행시킬 터미널창 고정
}
 
//test 종료
void test_kill(){
	printf("killed %d\n", get_pid());
	kill(get_pid(), SIGKILL); //죽이기
}
