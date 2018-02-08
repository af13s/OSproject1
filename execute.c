#include "functions.h"


void execute(struct PCMD cmd)
{

    if (cmd.bin1 == 0)
    {
        printf("Exiting Shell...\n" );
        exit(0);
    }


    //printf("backgroudn %d",cmd.background);
    //tempory fix for & in command

    if (cmd.background >= 1)
        cmd.CMD1[1] = NULL;
    printf("pipes: %d\n", cmd.pipe_num);

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

            if (cmd.bin1 > 0)
            {
                exec_builtin(cmd);
                return;
            }

            execv(cmd.CMD1[0],cmd.CMD1);
        }
      else
        {
        	// parent thread waiting
        	call_wait(pid,cmd);
        }
}