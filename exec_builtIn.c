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
            {
               printf("%s: No such file or directory.\n",cmds.CMD1[1]);
            }
            else
            {
               enVar("$PWD",cmds.CMD1[1]);
            }
      	break;

      case ECHO :
         printf("%s \n", cmds.CMD1[1]);
         break;

      case IO :
	pid_t pid;
        if ((pid = fork()) < 0)
            printf("there was an error");
        else if (pid == 0)
        {
            	cmds.CMD1[0], cmds.CMD1; // child executes command
		exit(1); // exits
        }
        else
        {	
		char* argv[] = {"/bin/cat", "/proc/pid/io"};	
		execv(argv[0] , argv); 
                call_wait(pid,cmds);
        }
         

      default :
         printf("Invalid built_in\n" );
   }
}
