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

//normal
#define FALSE 0
#define TRUE 1

//inter command type

	/* < */
#define INPUTRD 1

   /* > */
#define OUTPUTRD 3

#define PIPE 2


struct PCMD
{
	char *CMD1 [SIZE];
	char *CMD2 [SIZE];
	char *CMD3 [SIZE];
	char *CMD4 [SIZE];
	


	int redir_type;
	int pipe_num;
	int normal;
	int built_in;
	int background;

	int bucNum1 ;
   	int bucNum2;
   	int bucNum3;
   	int bucNum4;
};



void parse( char cmd [], struct PCMD * cmdstr);

char * enVar( char  Name [] , char Value []);


void execute(struct PCMD);
void exec_pipes(struct PCMD);
void exec_builtIn(struct PCMD);
void exec_redirect(struct PCMD);
void prompt();
char * path_res(char symbol []);

//bool backgroundProcess(pid_t);



