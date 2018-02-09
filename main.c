#include "functions.h"

int memoryAlloc = FALSE;

int main()
{
  
  char input_line [256];
  pid_t * bqueue = (pid_t*) calloc(10, sizeof(pid_t));
  bqueue[0] = 10;
  int bgcount =1;

  while(1)
  {
    struct PCMD parsed;
    parsed.bqueue = bqueue;
    prompt();
    fgets(input_line, 255, stdin);
    parse(input_line, &parsed);

    parsed.bgcount = &bgcount;
    int i;

    if (parsed.background >= 1)
    {
      parsed.bgcmds[*parsed.bgcount] = (char*) calloc(strlen(input_line), sizeof(char*));
      strcpy(parsed.bgcmds[*parsed.bgcount],input_line);
      //printf("parsed.bgcmds: %s",parsed.bgcmds[i]);
    }

    execute(parsed);
  }

}
