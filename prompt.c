#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functions.h"

void prompt()
{
	// example provided USER@MACHINE :: PWD =>
	// dennis@linprog3 :: /home/grads/dennis/cop4610t => 
	printf("%s@%s::%s =>",enVar("$USER",NULL),enVar("$MACHINE",NULL),enVar("$PWD",NULL));
}