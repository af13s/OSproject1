#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "functions.h"


void execute(struct PCMD cmd)
{
	pid_t pid;

	if((pid = fork()) == -1)
        {
          printf("Error creating child in execute");
        }
      else if (pid == 0)
        {
            //printf("child was created");
          //Execute command in new process
        	//int redir_type, int pipe_num, normal, built_in, background
        	if (cmd.redir_type != 0)
        	{
        		exec_redirect(cmd);
        		return;
        	}

        	if (cmd.pipe_num > 0)
        	{
        		exec_pipes(cmd);
        		return;
        	}

            //printf("reached execution stage");
            execv(cmd.CMD1[0],cmd.CMD1);
        }
      else
        {
        	// parent thread waiting
        	wait(NULL);
        }
}