#include <unistd.h>
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

#define EXIT_FAILURE 1

void exec_redirect(struct PCMD cmds)
{
	int fd = open(cmd.[1])
	pid_t pid;
	//If we need file input "cmd < file" (redirection type 0)
	if(cmds.redir_type == 0){
		if(pid = fork() == 0){
			close(STDOUT_FILENO);
			dup(fd,0);
			close(fd);
			
		//Execution
			execv(cmd.CMD4 , NULL);
		}		
		
	}
	//If we need file output "cmd < file" (redirection type 1)
	if(cmds.redir_type == 1){
		if (pid = fork() == 0){
			close(STDIN_FILENO); 
			dup(fd,1);
			close(fd);
		
		//Execution 
			execv(cmd.CMD4 , NULL);  		
		}
		if(pid = fork() == -1){
		printf(" Error: unable to write to file "); 	
		
		}
		

	}

}

