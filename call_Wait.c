#include "functions.h"
//background process #define FORE 0 // #define BACK 1 // #define BACKPID -1

//Execute CMD in the background
//When execution starts, print [position of CMD in the execution queue] [CMD's PID]
//When execution completes, print [position of CMD in the execution queue]+[CMD's command line]


void call_wait(pid_t child, struct PCMD cmds)
{	
	int queue_num = 0;
	int status;
	pid_t ret;

	if (cmds.background == FORE) 		// FORE (0) == not background process
	{
		waitpid(child, &status, FORE);
	}
	else
	{
		queue_num = add_child(cmds.bqueue, child);
		//printf("[queue number] 	[pid]\n");
		printf("[%d] 	[%d]\n",queue_num, child);

		waitpid(-1, &status, WNOHANG);

		if (status > 0)
		{
			queue_num = remove_child(cmds.bqueue, child); 
			//printf("[queue number]+ 	[cmd]\n");
			printf("[%d]+  ", queue_num);
			printlastcmd(cmds);
		}
	}
}

int add_child(pid_t * queue, pid_t child)
{
	if (queue[queue[0]-2] != 0)
		 resize_queue(queue);

	int i;
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
	int i;
	for ( i = 1; i < queue[0]; i++)
		if (queue[i] == child)
		{
			queue[i] = 0;
			return i;
		}

	return 0;
}

void resize_queue(pid_t * oldqueue)
{
	pid_t *newqueue = (pid_t*) calloc((oldqueue[0]*2), sizeof(pid_t));
	newqueue[0] = (oldqueue[0]*2);

	int i;

	for (i = 0; i < oldqueue[0]; i++)
		newqueue[i] = oldqueue[i];

	free(oldqueue);

	oldqueue = newqueue;
}

void printlastcmd(struct PCMD pcmd)
{
	printf("[");
	char ** cmd [] = {pcmd.CMD4,pcmd.CMD3,pcmd.CMD2,pcmd.CMD1};

	int i;
	int j = 0;

	for (i = 0; i < 4; i++)
	{
		if (cmd[i][0] == NULL)
			continue;
		else
			while(cmd[i][j] != NULL)
				{
					printf(" %s " , cmd[i][j]);
					j++;
				}
			printf("] \n");
			break;
	}
}




