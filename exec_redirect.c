#include "functions.h"

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
	    	close(1);
	        dup2(fd,STDIN_FILENO);
	        close(fd);
	    }

	    if (cmds.redir_type == OUT)
	    {
	    	fd = open(cmds.CMD2[0], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	    	close(1);
	        dup2(fd,STDOUT_FILENO);
	        close(fd);
	    }

	    execv(cmds.CMD1[0], cmds.CMD1);
	    printf("Failed to exec %s\n", cmds.CMD1[0]);
	    exit(1); 
	}

	else
	{
	 	call_wait(pid,cmds);
	}
}


