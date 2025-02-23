#include "functions.h"

void parse_whitespace(char*  line);
void sepBych(char ch, char * line);
char* makearg(char * arg);
char * check4bin(char* cmd, int * bintype);
char *  commandPath(char*);
extern int memoryAlloc;






void parse(char cmd [], struct PCMD * cstruct )
{
   int i = 0;

   char * tempBucket[50];
   int tbucNum = 0;

   cstruct->bucNum1 = 0;
   cstruct->bucNum2 = 0;
   cstruct->bucNum3 = 0;
   cstruct->bucNum4 = 0;
   cstruct->invalid = 0;

   int numComs = 1;
   for(i = 0; i < 50; i++)
   {
   	if(cstruct->CMD1[i] && memoryAlloc)
   	  free(cstruct->CMD1[i]);

   	if(cstruct->CMD2[i] && memoryAlloc)
   	  free(cstruct->CMD2[i]);
   	
   	if(cstruct->CMD3[i]&& memoryAlloc)
   	  free(cstruct->CMD3[i]);
   	
   	if(cstruct->CMD4[i]&& memoryAlloc)
   	  free(cstruct->CMD4[i]);
    
      cstruct->CMD1[i] = NULL;
      cstruct->CMD2[i] = NULL;
      cstruct->CMD3[i] = NULL;
      cstruct->CMD4[i] = NULL;
      tempBucket[i] = NULL;
   }

      
   char * sp, * ecp, *tempp;

  parse_whitespace(cmd);
  
   
   cstruct->pipe_num = 0;
   cstruct->background =0;
   cstruct->redir_type=0;


   

   
   for(i = 0; cmd[i]; i++)
   {
   		
   		if(cmd[i] == '<')
   			cstruct->redir_type = IN;
   		else if (cmd[i] == '>')
   			cstruct->redir_type = OUT;
   		else if(cmd[i] == '&' && !cmd[i+1] )
   		{
   			cmd[i] = ' ';
   			cstruct->background++;
   		}
   		else if(cmd[i] =='&' && i == 0)
   		{
   			cmd[i] = ' ';
   			
   		}
   		else if(cmd[i] == '&' && cmd[i+1])
   		{
   			cmd[i] = ' ';
   			cstruct->invalid = 1;
   		}
   		else if(cmd[i] == '|')
   			cstruct->pipe_num++;
   		
   }
	parse_whitespace(cmd);

	ecp = cmd + strlen(cmd) + 1;
   
   for(i = 0;cmd[i]; i++)
   {
   		if(cmd[i] == ' ')
   		{
   			cmd[i] = '\0';
   		}
   }
      
   for(sp = tempp = cmd; tempp != ecp; tempp++ )
   {

   		if(!*tempp)
   		{
   			tempBucket[tbucNum++] = makearg(sp);
   			if(tempp < ecp - 1)
   			{
   				sp = tempp + 1;
   			}
   		}
   }

   char targ[50];
   for(i = 0; i < tbucNum; i++)
   {
   		if((!strcmp("<",tempBucket[i]) || !strcmp(">",tempBucket[i]) || !strcmp("|",tempBucket[i]) ) && i > 0)
   			numComs++;
   		else
   		{
	   		if(numComs == 1)
	   			cstruct->CMD1[cstruct->bucNum1++] = tempBucket[i];
	   		if(numComs == 2)
	   			cstruct->CMD2[cstruct->bucNum2++] = tempBucket[i];
	   		if(numComs == 3)
	   			cstruct->CMD3[cstruct->bucNum3++] = tempBucket[i];
	   		if(numComs == 4)
	   			cstruct->CMD4[cstruct->bucNum4++] = tempBucket[i];
   		}	

   }

   /*Check for builtins*/
   cstruct->CMD1[0] = check4bin(cstruct->CMD1[0],&cstruct->bin1);
   cstruct->CMD2[0] = check4bin(cstruct->CMD2[0],&cstruct->bin2);
   cstruct->CMD3[0] = check4bin(cstruct->CMD3[0],&cstruct->bin3);
   cstruct->CMD4[0] = check4bin(cstruct->CMD4[0],&cstruct->bin4);

   
   /*check for path expansion*/

  	if(cstruct->bin1 == CD)
   		cstruct->CMD1[1] = expandCD(cstruct->CMD1[1]);


}


void parse_whitespace(char* line)
{


	int i = 0,j = 0;

	/* ignore & before command*/
	while(isspace(line[i]))
		i++;
	if(line[i] == '&')
		line[i] = ' ';
	i = 0;

	/*Removing leading white space*/
	
	while(isspace(line[i]))
		i++;
	for(j = i; line[j]; j++)
		line[j-i] = line[j];

	line[j-i] = line[j]; /*for \0 */

	i = j = 0;

	/*Removing trailing whitespace*/	

	for(i = strlen(line) - 1;isspace(line[i]); i-- )
		j++; 


	line[strlen(line) - j] = '\0';




	/* Remove spaces in between */

	i = j = 0 ;
	for(i =0; line[i] != '\0'; i++)
	{
		if(!isspace(line[i]) || ( i > 0 && !isspace(line[i - 1])) )
		{
			line[j] = line[i];
			j++;
		}
	}
	line[j] = '\0';


	/* Seperating between certain characters*/
	sepBych('|',line);
	sepBych('<',line);
	sepBych('>',line);
	


}

/*makes sure there are spaces between special chars*/
/* | < > & $ ~ */
void sepBych(char ch, char * line)
{

	char copy[512];
	int i,j;
	for(i = 0; line[i];i++)
	{	
		if(i > 0  && line[i] == ch && line[i -1] != ' ')
		{
			strcpy(copy,line+i);
			line[i] = ' ';
			line[i+1] = '\0';
			strcat(line,copy);
		}

		if(i < strlen(line) -1 && line[i] == ch && line[i + 1] != ' ')
		{
			strcpy(copy,line+i+1);
			line[i + 1] = ' ';
			line[i+2] = '\0';
			strcat(line,copy);
		}
	}
	

}

char * makearg(char * arg)
{
   memoryAlloc = TRUE;
   char * temp = NULL;
   char * storage;
   char * rest = NULL;
   int i = 0;

   if(arg[0] == '$' && arg[1])
   {

      for(i = 0;arg[i]; i++)
      {
         if(arg[i] == '/' && arg[i+1])
         {
            arg[i] = '\0';
            rest = arg + i+1;
            break;
         }
      } 
      temp = enVar(arg,NULL);
      
   }
   if(temp && !rest)
   {
      storage = (char *)calloc(strlen(temp) + 1,1);
      strcpy(storage,temp);
      return storage;
   }
   if(temp && rest)
   {
      storage = (char*)calloc(strlen(temp) + strlen(rest) + 2,1);
      strcpy(storage,temp);
      strcat(storage,"/");
      strcat(storage,rest);
      return storage;
   }

   storage = (char *)calloc(strlen(arg) + 1,1);
   strcpy(storage,arg);
   return storage;
}

char * check4bin(char * cmd,int * bintype)
{
	if(cmd && !strcmp(cmd,"echo"))
		*bintype = 2;

	else if(cmd && !strcmp(cmd,"exit"))
		*bintype = 0;

	else if(cmd && !strcmp(cmd,"cd"))
		*bintype = 1;

	else if(cmd && !strcmp(cmd,"etime"))
		*bintype = 3;

	else if(cmd && !strcmp(cmd,"io"))
		*bintype = 4;
	else
		*bintype = -1;

	if (cmd && *bintype == -1)
		cmd = commandPath(cmd);

	return cmd;

}

