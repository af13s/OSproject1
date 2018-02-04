#include <unistd.h>
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <fcntl.h>

#define EXIT_FAILURE 1

void exec_redirect(struct PCMD cmds)
{
	int fd = open(cmds.CMD2,O_CREAT | O_RDWR);
	pid_t pid;
	//If we need file input "cmd < file" (redirection type 0)
	if(cmds.redir_type == 0){
		if((pid = fork()) == 0){
			close(STDOUT_FILENO);
			dup(fd);
			close(fd);
			
		//Execution
			execv(cmds.CMD1 , NULL);
		}		
		
	}
	//If we need file output "cmd < file" (redirection type 1)
	if(cmds.redir_type == 1){
		if ((pid = fork()) == 0){
			close(STDIN_FILENO); 
			dup(fd);
			close(fd);
		
		//Execution 
			execv(cmds.CMD1 , NULL);  		
		}
		if((pid = fork()) == -1){
		printf(" Error: unable to write to file "); 	
		
		}
		

	}

}

