#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

int main()
{
  
  char input_line [256];

  while(1)
  {
    struct PCMD parsed;
    prompt();
    fgets(input_line, 255, stdin);
    printf("sending command to be parsed: %s", input_line);
    parse(input_line, &parsed);
    execute(parsed);
  }
}
