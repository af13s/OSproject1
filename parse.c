#include "functions.h"
#include <ctype.h>
#include <string.h>

void parse_whitespace(char*  line);
void sepBych(char ch, char * line);
char* makearg(char * arg);


int parseStart = 0;
int main()
{

	int i;
	struct PCMD tcmd;
	char x[] = "This iis | a test  &    |hello| &jhgjhgjgjh";

	//parse_whitespace(x);
	//printf("%s\n",x );

	
	parse(x,&tcmd);
	for(i = 0; i < tcmd.bucNum1; i++)
	{
		printf("B1: %s\n", tcmd.CMD1[i]);
	}

	for(i = 0; i < tcmd.bucNum2; i++)
   {
   	printf("B2: %s\n",tcmd.CMD2[i] );
   }

   for(i = 0; i < tcmd.bucNum3; i++)
   {
   	printf("B3: %s\n",tcmd.CMD3[i] );
   }

   for(i = 0; i < tcmd.bucNum4; i++)
   {
   	printf("B4: %s\n",tcmd.CMD4[i] );
   }
	return 0;
	
}

void parse(char cmd [], struct PCMD * cstruct )
{
   int i = 0;

   char * tempBucket[50];
   int tbucNum = 0;

   cstruct->bucNum1 = 0;
   cstruct->bucNum2 = 0;
   cstruct->bucNum3 = 0;
   cstruct->bucNum4 = 0;

   int numComs = 1;
   for(i = 0; i < 50; i++)
   {
   	if(cstruct->CMD1[i] && parseStart)
   	  free(cstruct->CMD1[i]);

   	if(cstruct->CMD2[i] && parseStart)
   	  free(cstruct->CMD2[i]);
   	
   	if(cstruct->CMD3[i]&& parseStart)
   	  free(cstruct->CMD3[i]);
   	
   	if(cstruct->CMD4[i]&& parseStart)
   	  free(cstruct->CMD4[i]);
    
      cstruct->CMD1[i] = NULL;
      cstruct->CMD2[i] = NULL;
      cstruct->CMD3[i] = NULL;
      cstruct->CMD4[i] = NULL;
      tempBucket[i] = NULL;
   }

   parse_whitespace(cmd);
   printf("%s\n",cmd );
   char * sp, * ecp, *tempp;

  
   ecp = cmd + strlen(cmd) + 1;
   cstruct->pipe_num = 0;

   for(i = 0; cmd[i]; i++)
   {
   		if(cmd[i] == '<')
   			cstruct->redir_type = LEFT;
   		else if (cmd[i] == '>')
   			cstruct->redir_type = RIGHT;
   		else if(cmd[i] == '&')
   			cstruct->background++;
   		else 
   			cstruct->pipe_num++;
   		
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
/*
   for(i = 0; i < bucNum1; i++)
   {
   	printf("%s\n",cstruct->CMD1[i] );
   }

   for(i = 0; i < bucNum2; i++)
   {
   	printf("%s\n",cstruct->CMD2[i] );
   }

   for(i = 0; i < bucNum3; i++)
   {
   	printf("%s\n",cstruct->CMD3[i] );
   }


   */
   
/*
   for(i = 0; cmd[i]; i++)
   {
   		if(cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
   		{
   			if(cmd[i] == '<')
   				cstruct->redir_type = LEFT;
   			else if (cmd[i] == '>')
   				cstruct->redir_type = RIGHT;
   			else 
   				pipe_num++;

   			if(!cm1)
   				cm1 = cmd;
   			else
   			{
   				if(!cm2)
   					cm2 = cm1 + 1;
   				else
   				{
   					if(!cm3)
   						cm3 = cm2 + 1;
   					else
   					{
   						cm4 = cm3 + 1;

   					}
   				}
   			}
   		}
   }

   if (!cm1)
   		cm1 = cmd;

   for(i = 0; cmd[i]; i++)
   {
   		if(cmd[i] == ' ')
   		{
   			cmd[i] == '\0';
   		}
   }

   char * temp1,temp2;
   int numbucs = 0;
   if(!cm2)
   {
   		for(temp1 = temp2 = cm1; temp1 != cmd[strlen(cmd)]; temp1++)
   		{
   			if( ! *temp1 )
   			{
   				makearg(temp2,cstruct->CMD1[numbucs]);
   				numbucs++;
   				temp2 = ++temp1;
   			}
   		}

   		fillbuckets(cm1,cm1 + strlen(cmd) + 1, cstruct->CMD1);

   }

   else if(!cm3)
   {
   		fillbuckets(cm1,cm2+1, cstruct->CMD1);
   		fillbuckets(cm2,cm1 + strlen(cmd) + 1,cstruct->CMD2);
   }
   else if(!cm4)
   {
    	fillbuckets(cm1,cm2+1, cstruct->CMD1);
   		fillbuckets(cm2,cm3+1,cstruct->CMD2);
   		fillbuckets(cm3,cm1 + strlen(cmd) + 1,cstruct->CMD3);
   }
   else
   {
   		fillbuckets(cm1,cm2+1, cstruct->CMD1);
   		fillbuckets(cm2,cm3+1,cstruct->CMD2);
   		fillbuckets(cm3,cm4 + 1, cstruct->CMD3);
   		fillbuckets(cm4,cm1 + strlen(cmd) + 1,cstruct->CMD4);
   }
*/





}


void parse_whitespace(char* line)
{

	int i = 0,j = 0;

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
	for(i; line[i] != '\0'; i++)
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
	sepBych('&',line);
	sepBych('$',line);
	sepBych('~',line);

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
   char * storage = (char *)malloc(strlen(arg) + 1);
   strcpy(storage,arg);
   return storage;
}

/*
void fillbuckets(char* start, char* stop, char ** arr)
{
	char * temp1, * temp2;
	int numbucs = 0;
	for(temp1 = temp2 = start; temp1 != stop; temp1++)
   		{
   			if( ! *temp1 )
   			{
   				//makearg(temp2,arr[numbucs]);
   				numbucs++;
   				temp2 = ++temp1;
   			}
   		}

}
*/
