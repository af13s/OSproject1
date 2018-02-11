#include "functions.h"
//background process #define FORE 0 // #define BACK 1 // #define BACKPID -1

//Execute CMD in the background
//When execution starts, print [position of CMD in the execution queue] [CMD's PID]
//When execution completes, print [position of CMD in the execution queue]+[CMD's command line]

void call_wait(pid_t child, struct PCMD cmds)
{	
	int queue_num = 0;
	int child_state;
	int i;
	int ret;

	if (cmds.background == FORE)		// FORE (0) == not background process
	{
		ret = waitpid(child, NULL, FORE);

		for(i=1; i < cmds.bqueue[0];i++)
		{
			if (ret == cmds.bqueue[i])
			{
				queue_num = remove_child(cmds.bqueue,ret);
				printf("[%d]+	\n",queue_num);
				printcmd(cmds,queue_num);
				removebgcmd(queue_num,cmds);
			}
		}
	}
	else
	{
		queue_num = add_child(cmds.bqueue, child);
		printf("[%d] 	%d\n",queue_num, child);
		addbgcmd(queue_num,cmds);

		ret = waitpid(-1, &child_state, WNOHANG);

		if (ret > 0)
		{	
			queue_num = remove_child(cmds.bqueue,ret);
			printf("[%d]+	",queue_num);
			printcmd(cmds,queue_num);
			removebgcmd(queue_num,cmds);
		}
	}
}

int add_child(pid_t * queue, pid_t child)
{
	int i=1;
	for ( i = 1; i < queue[0]; i++)
		if (queue[i] == 0)
		{
			queue[i] = child;
			return i;
		}

	return 0;
}

int remove_child(pid_t * queue, pid_t child)
{
	int i=1;
	for ( i = 1; i < queue[0]; i++)
		if (queue[i] == child)
		{
			queue[i] = 0;
			return i;
		}

	return 0;
}

void addbgcmd(int queue_num,struct PCMD pcmd)
{
	pcmd.originalcmd[strlen(pcmd.originalcmd)-2] = '\0';
	pcmd.bgcmds[queue_num] = (char*) calloc(strlen(pcmd.originalcmd+1), sizeof(char));
	strcpy(pcmd.bgcmds[queue_num], pcmd.originalcmd);
}

void removebgcmd(int queue_num,struct PCMD pcmd)
{
	free(pcmd.bgcmds[queue_num]);
	pcmd.bgcmds[queue_num] = NULL;
}

void printcmd(struct PCMD pcmd, int queue_num)
{
	printf("%s\n",pcmd.bgcmds[queue_num]);
}




