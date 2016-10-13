#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_MAX 1024

void copy_file(char *src_file,unsigned short dot_cycle){
	char output_file[BUF_MAX], block[BUF_MAX];
	int in, out, nread;
	unsigned short cnt_out=0;

	//복사할 파일명 만들기 원본파일명+_copy
	strcpy(output_file,src_file);
	strcat(output_file,"_copy");

	//읽기전용으로 파일읽기 실패시 -1
	in = open(src_file,O_RDONLY);
	if(in == -1){
		printf("%s 파일을 읽을 수 없습니다.\n",src_file);
		exit(0);
	}

	//쓰기전용으로 파일읽고 없으면 파일 생성, 소유자 읽기쓰기 권한
	out = open(output_file, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	if(out == -1){
		printf("%s 파일을 생성할 수 없습니다. \n",output_file);
		exit(0);
	}

	//in파일 서술자에서 block버퍼에 최대 sizeof(block)만큼 읽기
	//읽은 바이트 만큼 nread에 저장
	while((nread = read(in,block,sizeof(block))) > 0){
		//out 파일 서술자에 block에 있는 데이터를 nread만큼 쓰기
		write(out,block,nread);
		if(cnt_out++==dot_cycle){
			cnt_out=0;
			printf(".");
		}
	}
	close(in);
	close(out);
	puts("");
	puts("file copy complete.");
}
int main(int argc, char** argv) {

	switch(argc){
		case 1:
			copy_file(argv[0],10);
			break;
		case 2:
			copy_file(argv[1],10);
			break;
		default :
			printf("인자가 너무 많습니다.\n");
			exit(0);
	}
	
}
