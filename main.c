#include "functions.h"

int memoryAlloc = FALSE;

int main()
{
  
  char input_line [256];
  pid_t * bqueue = (pid_t*) calloc(25, sizeof(pid_t));
  char ** bgcmds = (char **) calloc(25, sizeof(char*));
  char * originalcmd = (char*) calloc(strlen(input_line+1), sizeof(char));
  bqueue[0] = 25;
  int i, status;

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

    // wait for processes to finish and release memory
    if(!strcmp("exit",parsed.CMD1[0]))
    {
      for(i=1; i < parsed.bqueue[0];i++)
            if (parsed.bqueue[i] != 0)
            {
               while (waitpid(parsed.bqueue[i],&status,0) == 0);
               printf("[%d]+   ",i);
               printcmd(parsed,i);
               removebgcmd(i,parsed);
            }
      printf("Exiting Shell...\n");
      break;
    }

    execute(parsed);
  }
}

void freeMem(char ** ST,int size)
{
  int i; 
  for(i = 0; i < size; i++)
  {
      free(ST[i]); 
      ST[i] = NULL;
  }


}