#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>


int printdir(char *dir, int depth){

  DIR *dp;
  struct dirent *entry;
  struct stat statbuf;

  if ((dp = opendir(dir)) == NULL) {
    fprintf(stderr, "cannot open %s\n", dir);
    return;
  }
  chdir(dir);

  while ((entry = readdir(dp)) != NULL) {
     lstat(entry->d_name, &statbuf);
     if (S_ISDIR(statbuf.st_mode)) {
	 if ((strcmp(".", entry->d_name) == 0) ||
		 strcmp("..", entry->d_name) == 0)
			 continue;
	 printf("%*s%s/\n", depth, " ", entry->d_name);
	 printdir(entry->d_name, depth+4);
     } else
	 printf("%*s%s\n", depth, " ", entry->d_name);
  }
  chdir("..");
  closedir(dp);
}

main(int argc, char*argv[]){

  if (argc < 2) {
     printf("Usage: %s directory\n", argv[0]);
     exit(1);
  }
  printdir(argv[1], 0);
}
