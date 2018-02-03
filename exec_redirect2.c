#include <unistd.h>
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void exec_redirect(struct PCMD cmds)
{
	pid_t pid;
	if ((pid = fork()) < 0)
	    printf("there was an error");

	else if (pid == 0)
	{
		

	    if (cmds.redir_type == IN)
	    {
	    	int fd = open(cmds.CMD2[0],O_RDONLY);
	        //int fd = open(cmds.CMD2[0]);
	        //close(STDIN_FILENO);
	        dup2(fd,STDIN_FILENO);
	        close(fd);
	    }

	    if (cmds.redir_type == OUT)
	    {
	    	int fd = open(cmds.CMD2[0],O_CREAT | O_TRUNC);
	        //int fd1 = open(cmds.CMD2[0]) ;
	        //close(STDIN_FILENO);
	        dup2(fd, STDOUT_FILENO);
	        close(fd);
	    }

	    execv(cmds.CMD1[0], cmds.CMD1);   // Or your preferred alternative
	    fprintf(stderr, "Failed to exec %s\n", cmds.CMD1[0]);
	    exit(1);
	}

	else
	{
	    wait(NULL);
	}
}


