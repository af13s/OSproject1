#include "functions.h"

int memoryAlloc = FALSE;

int main()
{
  
  char input_line [256];
  pid_t * bqueue = (pid_t*) calloc(25, sizeof(pid_t));
  char ** bgcmds = (char **) calloc(25, sizeof(char*));
  char * originalcmd = (char*) calloc(strlen(input_line+1), sizeof(char));
  bqueue[0] = 25;

  while(1)
  {
    struct PCMD parsed;
    parsed.bqueue = bqueue;
    prompt();
    fgets(input_line, 255, stdin);
    parsed.originalcmd = originalcmd;
    parsed.bgcmds = bgcmds;
    strcpy(parsed.originalcmd,input_line);
    parse(input_line, &parsed);
    execute(parsed);
  }

}
