#include "functions.h"

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

      case  0:
         printf("Exiting Shell..." );
         return 0;
         break;

      case 1 :
      	break;

      case 2 :
         	echo(cmds.CMD2[0]);
         break;

      case 3 :
         printf("You passed\n" );
         break;

      case 4 :
         printf("Better try again\n" );
         break;

      default :
         printf("Invalid built_in\n" );
   }
}

void echo (char input [])
{

}