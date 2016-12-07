#include <stdio.h>
#include <stdlib.h>

extern int InFoo(), InBoo(), InBar();

int main()
{
  InFoo();
  InBoo();
  InBar();
  printf("hello world");
  exit(0);
 }
