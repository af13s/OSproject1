#include <unistd.h>
#include <stdio.h>
#include "functions.h"

void exec_pipe(struct PCMD input)
{
	int fd[2];
	int valid;
	
	valid = pipe(fd);
	
	if (valid == -1)
		printf("couldn't pipe");

	if (fork() == 0)
	{
	//Child (cmd1 | cmd2)
		if (fork() == 0)
		{
			//cmd1 (Writer)
			close(STDOUT_FILENO);
			dup(fd[1]);
			close(fd[0]);
			close(fd[1]);
			//Execute Command
			execv(input.CMD1[0],input.CMD1);
		}

		else 
		{
			//cmd2 (Reader)
			close(STDIN_FILENO);
			dup(fd[0]);
			close(fd[0]);
			close(fd[1]);
			//Execute Command
			printf("\n");
			execv(input.CMD2[0],input.CMD2);
		}
	}
	else
	{
		//Parent (Shell)
		close(fd[0]);
		close(fd[1]);
	}
}