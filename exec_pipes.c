#include <unistd.h>
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

#define EXIT_FAILURE 1

void exec_pipe(struct PCMD cmds)
{
	char **cm[] = {cmds.CMD1, cmds.CMD2, cmds.CMD3, NULL, NULL};
  int   p[2];
  pid_t pid;
	int   fd_in = 0;
	char *** cmd = cm;

  while (*cmd != NULL)
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          printf("Could not create child");
        }
      else if (pid == 0)
        {
          dup2(fd_in, 0); //change the input according to the old one 
          if (*(cmd + 1) != NULL)
            dup2(p[1], 1);
          close(p[0]);
          execvp((*cmd)[0], *cmd);
          exit(EXIT_FAILURE);
        }
      else
        {
          wait(NULL);
          close(p[1]);
          fd_in = p[0]; //save the input for the next command
          cmd++;
        }
    }
}