#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "functions.h"


void execute(struct PCMD cmd)
{
    printf("\n %d \n",cmd.redir_type);
    printf("\n %d \n",cmd.pipe_num);
    printf("\n %s\n",cmd.CMD1[0]);

    cmd.pipe_num = 0;

	pid_t pid;

	if((pid = fork()) == -1)
        {
          printf("Error creating child in execute");
        }
      else if (pid == 0)
        {
            printf("child was created");
          //Execute command in new process
        	//int redir_type, int pipe_num, normal, built_in, background
        	if (cmd.redir_type != NOT)
        	{
        		exec_redirect(cmd);
        		return;
        	}

        	if (cmd.pipe_num > 0)
        	{
        		exec_pipes(cmd);
        		return;
        	}
            printf("reached execution stage");
            execv(cmd.CMD1[0],cmd.CMD1);
        }
      else
        {
        	// parent thread waiting
        	wait(NULL);
        }
}