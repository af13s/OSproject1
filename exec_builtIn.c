#include "functions.h"
#include <sys/time.h>

//built_in
//#define EXIT 0
//#define CD 1
//#define ECHO 2
//#define ETIME 3
//#define IO 4

void exec_builtIn(struct PCMD cmds)
{
	switch(cmds.built_in) 
	{

      case  EXIT:
         printf("Exiting Shell..." );
         return 0;
         break;

      case CD :
         enVar("$PWD",cmds.CMD2[0])
      	break;

      case ECHO :
         printf("%s", cmds.CMD2[0])
         break;

      case ETIMEs:
         etime(cmds.CMD2);
         break;

      case IO :
         printf("Better try again\n" );
         break;

      default :
         printf("Invalid built_in\n" );
   }
}

void etime(char ** cmd)
{
   struct timeval start;
   struct timeval end;
   long double elapsed;

   gettimeofday(&start, NULL);

   if (fork() == 0)
      execv(*cmd,cmd);
   else
      WAIT(NULL);

   gettimeofday(&end, NULL);

   elapsed = (end.tv_sec - start.tv_sec);
   elapsed += ((end.tv_usec - start.tv_usec) / (1000.0*1000.0));
   printf("%d",elapsed);
}