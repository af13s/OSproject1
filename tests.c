#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()

{

	char line[256] = "&This&isatest&";

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





	char copy[256];
	
	for(i = 0; line[i];i++)
	{	
		if(i > 0  && line[i] == '&' && line[i -1] != ' ')
		{
			strcpy(copy,line+i);
			line[i] = ' ';
			line[i+1] = '\0';
			strcat(line,copy);
		}
	
	if(i < strlen(line) -1 && line[i] == '&' && line[i + 1] != ' ')
		{
			strcpy(copy,line+i+1);
			line[i + 1] = ' ';
			line[i+2] = '\0';
			strcat(line,copy);
		}

	}


	printf("%s\n", line);
}
