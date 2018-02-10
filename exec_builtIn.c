#include "functions.h"

//built_in #define EXIT 0 // #define CD 1 // #define ECHO 2 // #define ETIM 3 // #define IO 4

void exec_builtin(struct PCMD cmds)
{
   int success;
   pid_t pid;
   char path [256];
   
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
	
        if ((pid = fork()) < 0)
            printf("there was an error");
        else if (pid == 0)
        {
              cmds.CMD1[1] = commandPath(cmds.CMD1[1]);
              char ** basecommand = &cmds.CMD1[1];
              close(1);
            	execv(*basecommand, basecommand); // child executes command
		          exit(1); // exits
        }
        else
        {	
          snprintf(path, sizeof(path), "/proc/%d/io",pid);
		      char* argv[] = {"/bin/cat", path, NULL};
		      execv(argv[0] , argv); 
          call_wait(pid,cmds);
        }
         

      default :
         printf("Invalid built_in\n" );
   }
}
