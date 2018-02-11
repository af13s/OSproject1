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
    int ret;
    int i;

    //check status for completed children
    for(i=1; i < cmd.bqueue[0];i++)
    {
        ret = waitpid(-1, &status, WNOHANG);

        if (ret > 0)
        {   
            int queue_num;
            queue_num = remove_child(cmd.bqueue,ret);
            printf("[%d]+   ",queue_num);
            printcmd(cmd,queue_num);
            removebgcmd(queue_num,cmd);
        }
    }

    gettimeofday(&start, NULL);
	
	if((pid = fork()) == -1)
        {
          printf("Error creating child in execute");
        }
      else if (pid == 0)
        {
        	if (cmd.redir_type != 0)
        	{
                // handles redirection
        		exec_redirect(cmd);
        		return;
        	}

        	if (cmd.pipe_num > 0)
        	{
                // handles piping
        		exec_pipes(cmd);
        		return;
        	}

            if (cmd.bin1 == ETIM)
            {   
                //handles etime built-in
                cmd.CMD1[1] = commandPath(cmd.CMD1[1]);
                char ** basecommand = &cmd.CMD1[1];
                int ret = execv(basecommand[0],basecommand);
            }

            if (cmd.bin1 > 0)
            {
                //handles more builtins
                exec_builtin(cmd);
                return;
            }

            retur = execv(cmd.CMD1[0],cmd.CMD1);
            exit(0);
        }
      else
        {
            if (retur != -1)
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
