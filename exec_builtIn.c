#include "functions.h"
//built_in #define EXIT 0 // #define CD 1 // #define ECHO 2 // #define ETIM 3 // #define IO 4

void exec_builtin(struct PCMD cmds)
{
   int success;
   
	switch(cmds.bin1) 
	{
      case CD :
            success = chdir(cmds.CMD1[1]);
            if (success == -1)
               printf("%s: No such file or directory.\n",cmds.CMD2[0]);
      	break;

      case ECHO :
         printf("%s \n", cmds.CMD1[1]);
         break;

      case ETIM:
         etime(cmds.CMD2);
         break;

      case IO :
         //printf("Better try again\n" );
         break;

      default :
         printf("Invalid built_in\n" );
   }
}

void etime(char ** cmd)
{
   struct timeval start;
   struct timeval end;
   long double elapsed = 0;
   pid_t pid;
   int status;

   gettimeofday(&start, NULL);

   if ((pid = fork()) == 0)
      execv(*cmd,cmd);
   else
      {
         waitpid(pid,&status,0);
      }

   gettimeofday(&end, NULL);

   

   elapsed = (end.tv_sec - start.tv_sec);
   elapsed += ((end.tv_usec - start.tv_usec) / (1000.0*1000.0));
   printf("%LG \n",elapsed);
}

//void echo(char **)
//{
   
//}