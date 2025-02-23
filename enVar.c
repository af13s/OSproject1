#include "functions.h"

char * enVar( char namez [], char value [])
{
	// stripping $ from string before passing to getenv()
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