#include "builtins.h"
#include <stdio.h>
#include <string.h>


int builtin_echo(char **args, t_context *ctx)
{
    int i = 1; // Pula o "echo" (args[0])
    int newline = 1; // Por padrão, echo adiciona newline

	if (!args || !args[0])
	{
		printf("\n");
		ctx->exit_status = 0;
		return (0);
	}
    
    // Verifica se tem a flag -n (sem newline)
    if (args[1] && strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i = 2; // Pula o "echo" e o "-n"
    }
    
    //imprime os argumentos
    while (args[i])
    {
        printf("===> %s", args[i]);
        if (args[i + 1]) // Se não é o último argumento
            printf(" ");
        i++;
    }
    
    // Adiciona newline se necessário
    if (newline)
        printf("\n");
    
    ctx->exit_status = 0; // echo sempre retorna 0
    return (0);
}