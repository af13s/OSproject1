#define SIZE 50

//redir_type
#define NOT 0
#define LEFT 1
#define RIGHT 2

//built_in
#define EXIT 0
#define CD 1
#define ECHO 2
#define ETIME 3
#define IO 4

//normal
#define FALSE 0
#define TRUE 1



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
};


<<<<<<< HEAD
void parse( char cmd [], struct PCMD * cmdstr);
char * getEnVar( char string []);

char * enVar( char  Name [] , char Value []);
>>>>>>> 65aeef56454d0b8145875a8c0e8a738f78d5e4c3
void execute(struct PCMD);
void exec_pipes(struct PCMD);
void exec_builtIn(struct PCMD);
void exec_redirect(struct PCMD);
void prompt();
char * path_res(char symbol []);

//bool backgroundProcess(pid_t);



