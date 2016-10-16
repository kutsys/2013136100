
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf( "%s = %s\n", "$HOME", getenv( "HOME"));
	printf( "%s = %s\n", "$PS1", getenv( "PS1"));
	printf( "%s = %s\n", "$PATH", getenv( "PATH"));
	printf( "%s = %s\n", "$LD_LIBRARY_PATH ", getenv( "LD_LIBRARY_PATH "));

	printf("\nDefine the setenv\n");
	setenv("TEST_ENV", "1234",0); 
	printf("$TEST_ENV = %s\n", getenv("TEST_ENV"));
   return 0;
}
