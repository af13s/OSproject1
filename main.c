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

    // collect input from stdin
    scanf("%[^\n]%*c",input_line);

    // convert input into parsed CMD struct (PCMD) defined in functions.h
    parse(input_line,&parsed);

    execute(parsed);
    
  }
}
