#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdio.h>

int main(char* argv[])
{
    char block[1024];
    int nread;
    FILE* in;
    FILE* out;
    //동작 시간을 측정하기 위함
    clock_t newtime = 0; 
    clock_t oldtime = 0;
    double ElapsedTime = 0.0;
	
    char msg[16] = "Process in";

	//text.zip이 파일을 이너리 파일 읽기 전용으로 열기
    in = fopen("text.zip","rb");
	//copy.zip이라는 파일을 이너리 파일 쓰기 전용으로 열기
    out = fopen("copy.zip","wb");

    write(1,msg,16);
    
    oldtime = clock();

    while((nread = fread(block,sizeof(char),sizeof(block),in)) > 0){
	
	fwrite(block,sizeof(char),nread,out);
	
	newtime = clock();
	ElapsedTime = (double)(newtime - oldtime)/CLOCKS_PER_SEC;

	if(ElapsedTime >= 0.1) { //만약에 실행시간이 0.1보다 크다면
	    oldtime = clock();
            write(1,"*",1);//"*"을 출력
	    fflush(stdout);
	}
	

    }
    fclose(in);
    fclose(out);

}
