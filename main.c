#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

int main()
{
  struct PCMD parsed;
  char input_line [256];

  while(1)
  {
    prompt();

    // collect input from stdin
    input_line = scanf("%[^\n]%*c",line);

    // convert input into parsed CMD struct (PCMD) defined in functions.h
    parsed = parse(input_line);

    execute(parsed);
    
  }
}
