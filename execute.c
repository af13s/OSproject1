#include "functions.h"


void execute(struct PCMD cmd)
{

    struct timeval start;
    struct timeval end;
    double elapsed = 0;
    int status;
    int retur;
    pid_t pid;
    int queue_num;


    if (cmd.bin1 == 0)
    {
        printf("Exiting Shell...\n" );
        exit(0);
    }

    if (cmd.background >= 1)
        cmd.CMD1[2] = NULL;

    gettimeofday(&start, NULL);
	
	if((pid = fork()) == -1)
        {
          printf("Error creating child in execute");
        }
      else if (pid == 0)
        {
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

            if (cmd.bin1 == ETIM)
            {   
                cmd.CMD1[1] = commandPath(cmd.CMD1[1]);
                char ** basecommand = &cmd.CMD1[1];
                int ret = execv(basecommand[0],basecommand);
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
        	call_wait(pid,cmd);

            if (cmd.bin1 == ETIM)
            {
                gettimeofday(&end, NULL);
                elapsed = (end.tv_sec - start.tv_sec);
                elapsed += ((end.tv_usec - start.tv_usec) / (1000.0*1000.0));
                printf("%lf \n",elapsed);
            }

        }   
}
