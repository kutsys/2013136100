#include<stdio.h>
#include<stdlib.h>

int main(){
	printf("%s: %s\n", "HOME", getenv("HOME"));
	printf("%s: %s\n", "PS1", getenv("PS1"));
	printf("%s: %s\n", "PATH", getenv("PATH"));
	printf("%s: %s\n", "LD_LIBRARY_PATH", getenv("LD_LIBRARY_PATH"));
	return 0;
}
