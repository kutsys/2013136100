#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//Define bit flags
#define OPT_ELF_HEADER 0x1
#define OPT_PRO_HEADER 0x2
#define OPT_SEC_HEADER 0x4

int main(int argc, char* argv[]) {
	int opt = 0;
	char* exec = NULL;
	for(int i=1; i<argc; i++) {
		//if input parameter's first string is '-' then,
		if(argv[i][0]=='-') {
			int j=1;
			while(argv[i][j]!='\0') {
				//add following options to the opt variable (bit op)
				switch(argv[i][j]) {
					case 'e':
						opt |= OPT_ELF_HEADER;
						break;
					case 'p':
						opt |= OPT_PRO_HEADER;
						break;
					case 's':
						opt |= OPT_SEC_HEADER;
						break;
					default:
						printf("Warning. Unknown option: %c\n", argv[i][j]);
				}
				//repeat until zero-terminated string is detected
				j++;
			}
		} else	//pass parameter
			exec = argv[i];
	}
	if(exec==NULL) {
		printf("Error! Please input elf file name.\n");
		exit(EXIT_FAILURE);
	}
	
	//append options and parameter into readelf command
	char cmd[256] = "readelf -";
	if(opt==0 || (opt & OPT_ELF_HEADER))
		strcat(cmd, "h");
	if(opt & OPT_PRO_HEADER)
		strcat(cmd, "l");
	if(opt & OPT_SEC_HEADER)
		strcat(cmd, "S");
	strcat(cmd, " ");
	strcat(cmd, exec);
	system(cmd);

	exit(EXIT_SUCCESS);
}
