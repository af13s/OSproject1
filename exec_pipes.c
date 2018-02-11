#include "functions.h"

void exec_pipes(struct PCMD cmds)
{
	char **cm[5] = {NULL, NULL, NULL, NULL, NULL};
  int i;
  
  //setting char pointer pointers to each command that exists in parsed cmds
  for ( i= 0; i <= cmds.pipe_num; i++)
  {
      if (i == 0)
        cm[0] =  cmds.CMD1;
    
     if (i == 1)
        cm[1] = cmds.CMD2;

     if (i == 2)
        cm[2] = cmds.CMD3;
        
     if (i == 3)
        cm[3] = cmds.CMD4;
  }
  

  int   p[2];
  pid_t pid;
	int   in = 0;

  //will be used to iterate
	char *** cmd = cm;

  while (*cmd != NULL)
    {
      pipe(p);
       if ((pid = fork()) == 0)
        {
          dup2(in, 0); //based on old input change the input 

          if (*(cmd + 1) != NULL)
          {
            dup2(p[1], 1);
          }

          close(p[0]);
          execv((*cmd)[0], *cmd);
          printf("Failed to exec %s\n", cmds.CMD1[0]);
          exit(1); 
        }
        else if (pid == -1)
        {
          printf("Could not create child");
        }
      else
        {
          if (*(cmd + 1) == NULL)   // if it's the last command allow background process
            call_wait(pid,cmds); // wait for the child to finish
          else
            wait(NULL); // otherwise allow children to  completely finish
          close(p[1]);
          in = p[0]; //for the next command, the input is preserved
          cmd++;
        }
    }
}