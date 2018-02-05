#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

int memoryAlloc = FALSE;


int main()
{
  
  char input_line [256];

  while(1)
  {
    struct PCMD parsed;
    prompt();
    fgets(input_line, 255, stdin);
    //printf("sending command to be parsed: %s", input_line);
    parse(input_line, &parsed);
    //printf(parsed.CMD1[0]);
    //printf("%d",parsed.normal);
    //strcpy(parsed.CMD1[0],"/bin/ls");
    printf("\nenter execution function\n");
    printf("\n %s \n",parsed.CMD1[0]);
    printf("\n %s\n ",parsed.CMD1[1]);
    execute(parsed);
  }

}
