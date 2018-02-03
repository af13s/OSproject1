#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

char * enVar( char namez [], char value [])
{
	char * name = &namez[1];

	if (value == NULL)
	{
		char * envar = getenv(name);
		return envar;
	}
	else
	{
		int success;
		success = setenv(name, value, 1);

		if (success == -1)
			printf("setenv was not successful %s", strerror(errno));

		return getenv(name);
	}
}