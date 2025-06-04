#include "env.h"
#include <stdio.h>

void print_env(char **env)
{
	while (*env)
		printf("[ENV] %s\n", *env++);
}