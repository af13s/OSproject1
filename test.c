#include <stdio.h>
#include<sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "functions.h"

int main()
{

    /*************************** envar test *************************************/


    /*char string [] = "$AYEE";
    printf("%s" , enVar(string,"/AYEE"));*/

    /********* exec_pipes test ***************************************/
    char *cmd1 [50];
    char *cmd2 [50];
    char *cmd3 [50];

    char cmda[] = "/bin/ls";
    char cmdb[] = "/usr/bin/wc";
    char cmdc[] = "/usr/bin/wc";

    cmd1[0] = (char*)malloc(strlen(cmda)+1);
    cmd2[0] = (char*)malloc(strlen(cmdb)+1);
    cmd3[0] = (char*)malloc(strlen(cmdc)+1);

    strcpy(cmd1[0],cmda);
    strcpy(cmd2[0],cmdb);
    strcpy(cmd3[0],cmdc);

    // test CMD struct
    struct PCMD test;
    test.CMD1[0] = cmd1[0];
    test.CMD1[1] = NULL;

    test.CMD2[0] = cmd2[0];
    test.CMD2[1] = NULL;

    test.CMD3[0] = cmd3[0];
    test.CMD3[1] = NULL;

    test.redir_type = NOT;
    test.pipe_num = 2;
    test.normal = 1;
    test.background = 0;

    //printf("executing pipe\n");
    exec_pipes(test);
    //*////////////////////////////////////////////////////////////////////////////////


    /*char *argsv [2];
    char cmd[] = "/bin/ls";
    //char argument[] = "-l";
    
    argsv[0] = (char*)malloc(strlen(cmd)+1);
    argsv[1] = NULL;
    //argsv[1] = (char*)malloc(strlen(argument)+1);
    
    strcpy(argsv[0],argsv);*/


    //strcpy(argsv[1],argument);

    // testing PCMD struct
    // char *cmd1 [50];
    // char *cmd2 [50];

    // char cmda[] = "/bin/ls";
    // char cmdb[] = "/usr/bin/wc";

    // cmd1[0] = (char*)malloc(strlen(cmda)+1);
    // cmd2[0] = (char*)malloc(strlen(cmdb)+1);

    // strcpy(cmd1[0],cmda);
    // strcpy(cmd2[0],cmdb);

    // // test CMD struct
    // struct PCMD test;

    // test.CMD1[0] = cmd1[0];
    // test.CMD2[0] = cmd2[0];

    // test.redir_type = NOT;
    // test.pipe_num = 1;
    // test.normal = 1;
    // test.background = 0;


    //printf("%s",argsv[0]);
    //execv(*testing,testing);

    /*char line [256];
    char cmd [50][50];

    int r =0;
    r = scanf("%[^\n]%*c",line);

    int count = 0;
    
   while(scanf("%s",cmd[count]))
    {
        printf("captured: %s", cmd[count]);
        if 
        count++;
    }
    
    //char *argsv[2];
    //char cmd[] = "/bin/ls";
    
    //argsv[0] = (char*)malloc(strlen(cmd)+1);
    
    //strcpy(argsv[0],cmd);
    //execvp(argsv[0],argsv);
    //printf("%s",));
   // printf("%s",l);*/

    return 0;
}
