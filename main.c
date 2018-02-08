#include "functions.h"

int memoryAlloc = FALSE;


int main()
{
  
  char input_line [256];
  pid_t * bqueue = (pid_t*) calloc(100, sizeof(pid_t));
  bqueue[0] = 100;

  while(1)
  {
    struct PCMD parsed;
    parsed.bqueue = bqueue;
    prompt();
    fgets(input_line, 255, stdin);
    parse(input_line, &parsed);
    execute(parsed);
  }

}
