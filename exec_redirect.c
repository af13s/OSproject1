#include <unistd.h>
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void exec_redirect(struct PCMD cmds)
{
	// assumes pathname is in cmd2 and that redirect smybol thrown away
	int fd = open(cmds.CMD2[0], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

	pid_t pid;
	if ((pid = fork()) < 0)
	    printf("there was an error");

	else if (pid == 0)
	{
	    if (cmds.redir_type == IN)
	    {
	    	fd = open(cmds.CMD2[0], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	        //close(STDIN_FILENO);
	        dup2(fd,STDIN_FILENO);
	        close(fd);
	    }

	    if (cmds.redir_type == OUT)
	    {
	    	fd = open(cmds.CMD2[0], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	        dup2(fd,STDOUT_FILENO);
	        //close(STDOUT_FILENO); //not sure of this line may work without
	        close(fd);
	    }

	    execv(cmds.CMD1[0], cmds.CMD1);   // Or your preferred alternative
	    printf("Failed to exec %s\n", cmds.CMD1[0]);
	    exit(1); 
	}

	else
	{
	 	wait(NULL);
	}
}


