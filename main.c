#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

int main()
{
    //Testing pipe functions

    //set cmds to execute
    char *cmd1 [50];
    char *cmd2 [50];

    char cmda[] = "/bin/ls";
    char cmdb[] = "/usr/bin/wc";

    cmd1[0] = (char*)malloc(strlen(cmda)+1);
    cmd2[0] = (char*)malloc(strlen(cmdb)+1);

    strcpy(cmd1[0],cmda);
    strcpy(cmd2[0],cmdb);

    // test CMD struct
    struct PCMD test;

    test.CMD1[0] = cmd1[0];
    test.CMD2[0] = cmd2[0];

    test.redir_type = NOT;
    test.pipe_num = 1;
    test.normal = 1;
    test.background = 0;

    exec_pipe(test);

    return 0;
}
