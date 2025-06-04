#include "executor.h"
#include <string.h>
#include <stdio.h>
#include "builtins.h"

void	execute_command(t_command *cmd)
{
	if (strncmp(cmd->cmd, "echo", 4) == 0)
		builtin_echo(cmd->cmd + 5);
	else
		printf("comando não encontrado %s\n", cmd->cmd);
}
