#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

int main()
{
  
  char input_line [256];

  int run = 0;

  while(run != 3)
  {
    struct PCMD parsed;
    prompt();

    // collect input from stdin
    //scanf("%[^\n]%*c",input_line);
    //scanf("%s",input_line);


    // convert input into parsed CMD struct (PCMD) defined in functions.h
    //parsed = parse(input_line);

    //execute(parsed);
    run++;
  }
}
