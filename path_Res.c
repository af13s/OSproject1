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


char * expandCD(char * arg)
{

   int arglen = strlen(arg);

   char * pwd = enVar("$PWD",NULL);
   int pwdlen = strlen(pwd);
   char * home = enVar("$HOME",NULL);
   int homelen = strlen(home);

   char temppwd[250];
   strcpy(temppwd,arg);
   char * parent = NULL;
   char * ptr;
   int templen = 0;
   char * temp = NULL;
   int back = -1;
   int i = 0;
   char * tempr = arg;
   
   
   char targ[250];
   strcpy(targ,arg);


   int ndir = 1;
   char * rest = NULL;
   char first[50];
   
   

   
   for(i=0;targ[i];i++)
   {
      if(targ[i] == '/')
      {   
         if(targ[i + 1] != '\0')
         {
            rest = targ + i + 1;
         
         }

         
         break;
         
      }
   }


   if(arglen >= 1)
   {

      if(arg[0] == '~')
         back = 0; /*means a home dir*/

      else if(arglen >= 2 && arg[0] == '.' && arg[1] == '.')
      {
         back = 1;
         for(ptr = temppwd + pwdlen; *ptr != '/'; ptr--);
         *++ptr = '\0';
      }
      
   }

   if(back == 0)
   {
      if(arg)
         free(arg);
      if(rest)
      {
         arg = (char *)calloc(homelen + strlen(rest) + 2,1);
         strcpy(arg,home);
         strcat(arg,"/");
         strcat(arg,rest);
         return arg;
      }
      else
      {
         arg = (char *)malloc(homelen + 1);
         strcpy(arg,home);
         return arg;
      }
      
   }
   else if(back == 1)
   {
      if(arg)
         free(arg);
       if(rest)
      {
         arg = (char *)calloc(strlen(temppwd) + strlen(rest) + 2,1);
         strcpy(arg,temppwd);
         strcat(arg,"/");
         strcat(arg,rest);
         return arg;
      }
      else
      {
         arg = (char *)malloc(strlen(temppwd) + 1);
         strcpy(arg,temppwd);
         return arg;
      }
   }


   return arg;

}
