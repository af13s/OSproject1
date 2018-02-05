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
          //Execute command in new process
        	//int redir_type, int pipe_num, normal, built_in, background
        	if (cmd.redir_type != NOT)
        	{
        		exec_redirect(cmd);
        		return;
        	}

        	if (cmd.pipe_num > 0 && cmd.normal == TRUE)
        	{
        		exec_pipes(cmd);
        		return;
        	}

        	if (cmd.built_in > 0)
        	{
        		//exec_builtIn(cmd);
        		return;
        	}
        }
      else
        {
        	// parent thread waiting
        	wait(NULL);
        }
}