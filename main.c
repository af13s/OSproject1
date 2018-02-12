#include "functions.h"


int memoryAlloc = FALSE;

int main()
{
  
  char input_line [256] = {0};
  pid_t * bqueue = (pid_t*) calloc(25, sizeof(pid_t));  // background process queue
  char ** bgcmds = (char **) calloc(25, sizeof(char*)); // background process command name
  char * originalcmd = (char*) calloc(strlen(input_line+1), sizeof(char)); // store the original command
  bqueue[0] = 25;
  char temp[256];
  int count = 0;

  pid_t parent = getppid();

  while(1)
  {
    memset ( input_line, 0, 256 );
    struct PCMD parsed; // PCMD stands for parsed command, contains tokens and descriptors
    parsed.bqueue = bqueue;

    prompt(); // displays prompt based on environmental variabls


    fgets(input_line, 255, stdin);

    parsed.originalcmd = originalcmd; // sets pointer to original command
    parsed.bgcmds = bgcmds; // sets pointer to list of background commands list initialized above

    
    
      strcpy(parsed.originalcmd,input_line);
      parse(input_line, &parsed);

      // wait for processes to finish and release memory
      if(!strcmp("exit",parsed.CMD1[0]))
      {
        exit_shell(parsed);
        freeMem(parsed.CMD1,parsed.bucNum1);
        freeMem(parsed.CMD2,parsed.bucNum2);
        freeMem(parsed.CMD3,parsed.bucNum3);
        freeMem(parsed.CMD4,parsed.bucNum4);
        break;
      }

      execute(parsed);

      freeMem(parsed.CMD1,parsed.bucNum1);
      freeMem(parsed.CMD2,parsed.bucNum2);
      freeMem(parsed.CMD3,parsed.bucNum3);
      freeMem(parsed.CMD4,parsed.bucNum4);
    
  }

  free (bqueue);
  free (bgcmds);
  free (originalcmd);

  return 0; 
}

void exit_shell(struct PCMD parsed)
{
  int i, status;

  //checks for running processes, waits for completion and deallocates
  for(i=1; i < parsed.bqueue[0];i++)
            if (parsed.bqueue[i] != 0)
            {
               while (waitpid(parsed.bqueue[i],&status,0) == 0);
               printf("[%d]+   ",i);
               printcmd(parsed,i);
               removebgcmd(i,parsed);
            }
      printf("Exiting Shell...\n");
}

void freeMem(char * ST[],int size)
{
  int i; 
  for(i = 0; i < size; i++)
  {
      free(ST[i]); 
      ST[i] = NULL;
  }


}