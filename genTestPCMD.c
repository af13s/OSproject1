#include "functions.h"
#include <string.h>
#include <stdlib.h>

struct PCMD generateTestPCMD()
{
	char cmda[] = "/bin/ls";
    char cmdb[] = "testfile";
    char cmdc[] = "-l";

    char *cmd1 [50];
    char *cmd2 [50];

    
    cmd1[0] = (char*)malloc(strlen(cmda)+1);
    cmd1[1] = (char*)malloc(strlen(cmdc)+1);

    cmd2[0] = (char*)malloc(strlen(cmdb)+1);

    strcpy(cmd1[0],cmda);
    strcpy(cmd1[1],cmdc);

    strcpy(cmd2[0],cmdb);


    // test CMD struct
    struct PCMD test;
    test.CMD1[0] = cmd1[0];
    test.CMD1[1] = cmd1[1];
    test.CMD1[2] = NULL;

    test.CMD2[0] = cmd2[0];
    test.CMD2[1] = NULL;

    test.redir_type = OUT;
    test.pipe_num = 0;
    test.normal = 1;
    test.background = 0;

    return test;
}