#include "functions.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <unistd.h>
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

#include "functions.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h> 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functions.h"

#define SIZE 50

//redir_type
#define NOT 0
#define IN 1
#define OUT 2

//built_in
#define EXIT 0
#define CD 1
#define ECHO 2
#define ETIME 3
#define IO 4
#define NOTBIN -1

//normal
#define FALSE 0
#define TRUE 1

//inter command type
#define INPUTRD 1 /* < */
#define OUTPUTRD 3 /* > */



struct PCMD
{
	char *CMD1 [SIZE];
	char *CMD2 [SIZE];
	char *CMD3 [SIZE];
	char *CMD4 [SIZE];
	


	int redir_type;
	int pipe_num;
	int normal;
	
	int background;

	/*number of args in each cmd*/
	int bucNum1;
   	int bucNum2;
   	int bucNum3;
   	int bucNum4;

	/*if each cmd is built in*/
   	int bin1;
   	int bin2;
	int bin3;
	int bin4;


};



void parse( char cmd [], struct PCMD * cmdstr);
struct PCMD generateTestPCMD();
char * enVar( char  Name [] , char Value []);
void execute(struct PCMD);
void exec_pipes(struct PCMD);
void exec_builtIn(struct PCMD);
void exec_redirect(struct PCMD);
void prompt();
char * path_res(char symbol []);
char * commandPath(char *);

//bool backgroundProcess(pid_t);



