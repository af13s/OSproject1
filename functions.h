#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <dirent.h>

//standard size throughout
#define SIZE 50

//redir_type
#define NOT 0
#define IN 1
#define OUT 2

//built_in
#define EXIT 0
#define CD 1
#define ECHO 2
#define ETIM 3
#define IO 4
#define NOTBIN -1

//normal
#define FALSE 0
#define TRUE 1

//inter command type
#define INPUTRD 1 /* < */
#define OUTPUTRD 3 /* > */

//background process
#define FORE 0
#define BACK 1
#define BACKPID -1

//tokens for parsed command
struct PCMD
{
	char *CMD1 [SIZE];
	char *CMD2 [SIZE];
	char *CMD3 [SIZE];
	char *CMD4 [SIZE];
	
	/* Set to specify command type */
	int redir_type;
	int background;
	int pipe_num;
	int normal;

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

	//reference to background processes queue
	pid_t * bqueue;
	char ** bgcmds;
	char * originalcmd;
};

// parsed the command into tokens: PCMD struct
void parse( char cmd [], struct PCMD * cmdstr);

// Gets and Sets environment variables
char * enVar( char  Name [] , char Value []);

// Path resolution for commands and symbols
char * path_res(char symbol []);
char * commandPath(char *); // internal path_res function for command path resolution
char * expandCD(char*);

//executes commands that contains redirection
void exec_redirect(struct PCMD);

//executes bultin commands
void exec_builtin(struct PCMD);
void etime(char **);	// internal exec_builtIn function for etime
void echo(char **);		// internal exec_builtIn function for echo

//executes commands that contains pipes
void exec_pipes(struct PCMD);

//calls wait for (fore/back)ground processes
void call_wait(pid_t child, struct PCMD);
int add_child(pid_t * queue, pid_t child);
int remove_child(pid_t * queue, pid_t child);
void resize_queue(pid_t * oldqueue);
void printcmd(struct PCMD, int);
void addbgcmd(int, struct PCMD);
void removebgcmd(int,struct PCMD);

//decides which exec_function to run based on commands type (PCMD values)
void execute(struct PCMD);

//provides user prompt functionality (calls and displays requires environmental variables)
void prompt();

void exit_shell(struct PCMD);


