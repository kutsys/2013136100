#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>


void printdir(char *dir, int depth){

  DIR *dp; // 구조체 DIR의 포인터 변수
  struct dirent *entry;//구조체 dirent(디렉토리 엔트리) 포인터 변수
  struct stat statbuf;// 구조체 stat 버퍼 변수

  if ((dp = opendir(dir)) == NULL) {// 문자열 dir로 디렉토리 열었는데 비어 있으면
    fprintf(stderr, "cannot open %s\n", dir);  // 오류메시지 출력
    return;
  }
  chdir(dir);// 문자열 dir에 저장되어있는 디렉토리로 이동

// dp에 저장된 디렉토리 엔트리를 읽어들여 entry에 저장
// 저장된 값이 참인 동안 실행
  while ((entry = readdir(dp)) != NULL) {
     lstat(entry->d_name, &statbuf);// entry에 저장된 디렉토리명을 상태 버퍼에 저장
     if (S_ISDIR(statbuf.st_mode)) {// 상태버퍼의 모드 값을 검사하였는데, 디렉토리이면
	     /*Found a directory, but ignore . and.. */
	 if ((strcmp(".", entry->d_name) == 0) ||
		 strcmp("..", entry->d_name) == 0) // 문자열이 '.' 또는 '..'이면
			 continue;// 다음 엔트리 읽어들이기
	     // 디렉토리나 파일이면
	 printf("%*s%s/\n", depth, " ", entry->d_name);// 디렉토리 depth와 디렉토리명을 출력
	 /*Recurse at a new indent level */
	 printdir(entry->d_name, depth+4);// 디렉토리명으로 재귀호출
     } else// 디렉토리가 아니고 파일이면 
	 printf("%*s%s\n", depth, " ", entry->d_name);// depth와 파일명을 출력
  }
  chdir(".."); // 이전 디렉토리로 이동
  closedir(dp); // dp에 열려있는 디렉토리 닫기
}

//메인함
int main() {
	printf("Directory scan of /home:\n");
	printdir("/home",0);// 디렉토리 출력 함수 호출
	printf("done.\n");
	exit(0);
}
