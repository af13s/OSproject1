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

   if(access(cmd,F_OK) == 0)
      return cmd;
	else if(cmd && memoryAlloc)
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

   char targ[250];
   int i, dots = 0, home = 0;
   char * rest;
   char path[250];
   char p_pwd[250];
   char * ptr = NULL;
   int noArg = 0;
   //struct stat s;
  // if (stat(arg, &s) == 0 && S_ISDIR(s.st_mode))
    //  return arg;
   
   if(arg && arg[0] == '/')
      return arg;

   if(!arg)
   {
      strcpy(path,enVar("$HOME",NULL));
      arg = (char *)calloc(strlen(path),1);
      strcpy(arg,path);
      return arg;
   }
   strcpy(targ,arg);

   for(i = 0; targ[i] && targ[i] != '/'; i++)
   {
      if(targ[i] == '.')
         dots++;
      if(targ[i] == '~')
         home = 1;
   }

   if(!dots && !home)
      rest = targ;
   else
      rest = targ + i + 1;

   if(!arg )
   {
      home = 1;
      noArg = 1;
   }

   if(dots || home)
   {
      if(arg)
         free(arg);
   }

   if(home)
   {
      strcpy(path,enVar("$HOME",NULL));
      if(path[strlen(path) -1 ] != '/')
         strcat(path,"/");
      arg = (char * )calloc(strlen(path) + strlen(rest) + 1,1);
      strcpy(arg,path);
      if(*rest)
         strcat(arg,rest);
   }
   else if(dots == 1 || dots == 0)
   {
      strcpy(path,enVar("$PWD",NULL));
      if(path[strlen(path) -1 ]!= '/')
         strcat(path,"/");

      arg = (char *)calloc(strlen(path) + strlen(rest) + 1,1);
      strcpy(arg,path);
      if(*rest)
         strcat(arg,rest);
   }
   else if(dots == 2)
   {
      strcpy(path,enVar("$PWD",NULL));
      if( path[strlen(path) -1 ] != '/')
         strcat(path,"/");
      for(ptr = path + strlen(path) - 2; *ptr != '/';ptr--);
      *++ptr = '\0';
      arg = (char *)calloc(strlen(path) + strlen(rest) + 1,1);
      strcpy(arg,path);
      if(*rest)
         strcat(arg,rest);

   }

   return arg;



}


