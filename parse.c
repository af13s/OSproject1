#include "functions.h"
#include <ctype.h>
#include <string.h>

void parse_whitespace(char*  line);
void sepBych(char ch, char * line);
void makearg(char * arg, int index, char * storage);

struct PCMD parse(char cmd [], struct PCMD * cmdstr )
{
   int i = 0;
   parse_whitespace(cmd);

   for(i = 0; i < 50; i++)
   {
      CMD1[i] = NULL;
      CMD2[i] = NULL;
      CMD2[i] = NULL;
      CMD2[i] = NULL;
   }

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
			str[j] = line[i];
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
			strcpy(copy,line+i);
			line[i + 1] = ' ';
			line[i+2] = '\0';
			strcat(line,copy);
		}
	}
	

}

void makearg(char * arg,char * storage)
{
   storage = (char *)malloc(strlen(arg) + 1);
   strcpy(storage,arg);
}
