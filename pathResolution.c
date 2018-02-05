#include <unistd.h>
#include "functions.h"


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