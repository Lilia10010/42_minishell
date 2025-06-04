#include "builtins.h"
#include <stdio.h>

void builtin_echo(char *arg)
{
	printf("%s\n", arg);
}