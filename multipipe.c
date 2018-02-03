#include <unistd.h>
#include <stdio.h>
#include "functions.h"

void exec_pipe2(struct PCMD input)
{
	int fds[2 * input.pipe_num];
	char * cmd[SIZE];

	// open necessary amount of file descriptors
	for(i = 0; i < input.pipe_num; i++)
	{
        if(pipe(pipefds + i*2) < 0)
        {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }

	for(int i = 0; i < input.pipe_num; i+=2)
	{
		switch(i) 
		{

		   case 0  :
		      cmd = input.CMD1;
		      break;
			
		   case 1  :
		      cmd = input.CMD2;
		      break;

		   case 2  :
		      cmd = input.CMD3;
		      break;

		   case 3  :
		      cmd = input.CMD4;
		      break;

		   default :
		   printf("too many pipes");
			
		}

			//Child (cmd1 | cmd2 | ... )
			if (fork() == 0)
			{
				if (i < input.pipe_num)
				{
					//cmdprev (Writer)
					close(STDOUT_FILENO);
					dup2(pipefds[i + 1], 1)
					close(fd[0]);
					close(fd[1]);
				}
			
				if (i != 0)
				{
					//cmdnext (Reader)
					close(STDIN_FILENO);
					dup2(pipefds[i-2], 0)
					close(fd[0]);
					close(fd[1]);
				}

				//Execute Command
				execv(cmd[0],cmd);
			}
	}

	//Parent (Shell)
	/* parent closes all of its copies at the end */
	for( i = 0; i < 2 * num-pipes; i++ )
	{
		close(fds[i]);
	}

}