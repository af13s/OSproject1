#include "functions.h"


void execute(struct PCMD cmd)
{

    struct timeval start;
    struct timeval end;
    long double elapsed = 0;
    
    int status;

    if (cmd.bin1 == 0)
    {
        printf("Exiting Shell...\n" );
        exit(0);
    }

    gettimeofday(&start, NULL);
	pid_t pid;

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
                char * cmds[] = {"/bin/sleep", "20", NULL};
                int ret = execv(cmds[0],cmds);
                printf("%d\n",ret);
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
        	//call_wait(pid,cmd);
            waitpid(pid, &status, FORE);
            printf("%d", cmd.bin1);
        }

        if (cmd.bin1 == ETIM)
            {
                gettimeofday(&end, NULL);
                elapsed = (end.tv_sec - start.tv_sec);
                elapsed += ((end.tv_usec - start.tv_usec) / (1000.0*1000.0));
                printf("%LG \n",elapsed);
            }
}
