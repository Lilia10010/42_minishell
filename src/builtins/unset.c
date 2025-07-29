#include "builtin.h"
#include <stdio.h>

int builtin_unset(char **args, t_context *ctx)
{
	//todo este codigo é só de debug, retirar tudinho inho 
	(void)ctx;
	int i = 0;
	while (args[i])
	{
			printf("unset => %s\n", args[i]);
		++i;
	}
	return (0);
}