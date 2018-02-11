#include "functions.h"

int memoryAlloc = FALSE;

int main()
{
  
  char input_line [256];
  pid_t * bqueue = (pid_t*) calloc(10, sizeof(pid_t));
  bqueue[0] = 10;

  while(1)
  {
    struct PCMD parsed;
    parsed.bqueue = bqueue;
    prompt();
    fgets(input_line, 255, stdin);
    parsed.originalcmd = (char*) calloc(strlen(input_line+1), sizeof(char));
    strcpy(parsed.originalcmd,input_line);
    parse(input_line, &parsed);
    execute(parsed);
  }

}
