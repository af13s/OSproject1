#include <unistd.h>
#include "functions.h"
/*
Assumptions in this file:

The length of $PATH is less that 500 characters
The length of each path is less than 200 characters

*/

extern int memoryAlloc;


char *  commandPath(char * cmd)
{
	char paths[200][200];
	char allpaths[500];
	int i = 0;
	char temp[100];
	int path_found = 0;

	strcpy(allpaths,enVar("$PATH",NULL));

	int offset  = 0;
	while(i < 200 && sscanf(allpaths + offset,"%[^:]",paths[i]) == 1)
	{
		
		offset = offset + strlen(paths[i])+1;
	
		i++;
		
	}

	if(cmd && memoryAlloc)
	{
		int j = 0;
		for(j = 0; j < i-1;j++ )
		{
			strcat(paths[j],"/");
			strcat(paths[j],cmd);
			if(access(paths[j],F_OK) == 0)
			{
				path_found = 1;
				break;
			}
		}

		
		if(path_found)
		{
			free(cmd);	
			cmd = malloc(strlen(paths[j]) + 1);
			strcpy(cmd,paths[j]);
		}
	}
	return cmd;
	
}

char * expandCD(char * arg)
{

int arglen = strlen(arg);

char * pwd = enVar("$PWD",NULL);
int pwdlen = strlen(pwd);
char * home = enVar("$HOME",NULL);
int homelen = strlen(home);

char temppwd[250];

char * parent = NULL;
char * ptr;
int templen = 0;
char * temp = NULL;
int back = -1;
int i = 0;

strcpy(temppwd,pwd);

if(arglen > 1)
{

	if(arg[0] == '~' && arg[1] == '/')
		back = 0; /*means a home dir*/

	else if(arglen > 2 && arg[0] == '.' && arg[1] == '.' && arg[2] == '/')
	{
		back = 1;
		for(ptr = temppwd + pwdlen; *ptr != '/'; ptr--);
		*ptr = '\0';
	}
}

if(back = 0)
{
	if(arg)
		free(arg);
	arg = malloc(homelen + 1);

	strcpy(arg,home);
}
else if(back == 1)
{
	if(arg)
		free(arg);

	arg = malloc(strlen(temppwd) + 1);
	strcpy(arg,temppwd);
}




}