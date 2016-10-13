#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void LowCopy() {
	char buff_size[1024];
	int in ,out;
	int nread;

	// input file name = test.txt
	in = open("test.txt" , O_RDONLY);
	// output file name = result.txt
	//O_CREATE : 만약 pathname 파일이 존재하지 않을경우 파일을 생성한다. 
	//S_IRUSR : 00400 으로 사용자에게 읽기 권한을 준다. 
	//S_IWUSR : 00200 으로 사용자에게 쓰기 권한을 준다. 
	out = open("result.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	//만약에 읽어들인 데이터의 크기가 0보다 크면
	printf("start \n");

	while((nread =read(in,buff_size,sizeof(buff_size))) > 0) {
		// 파일이 복사되는 동안 "." 출력		
		printf(".");
		write(out,buff_size,nread);	
		//  1초마다 파일 복사
		sleep(1);	
	}
	printf("\nfinish\n");
}



int main() {
	LowCopy();	
	return 0;
}
