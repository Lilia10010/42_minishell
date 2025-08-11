/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aplly_heredoc_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:34:38 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/11 17:56:30 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "signals.h"
#include "command_types.h"
#include "lib_ft.h"
#include "context_types.h"
#include "lexer.h"
#include "env.h"

/*static void close_all_fds(void)
{
	int i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
} */

int aplly_heredoc_redirection(t_command *cmd, t_context *ctx)
{
    char    *line;
    int     fd;
    char    *file_name;
	char	*expanded_line;

    file_name = ".heredoc_tmp";
    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
    {
        perror("ERROR: aplly heredoc redirection open");
        return (0);
    }
    
    while (1)
    {
		signal(SIGINT, SIG_DFL);
        line = readline("> ");

        if (!line)
        {
            printf("warning: here-document delimited by end-of-file (wanted `%s')\n", 
                   cmd->heredoc_delimiter);
			ctx->exit_status = 0;
            close(fd);
            unlink(file_name);
			g_signal_received = -1;
			//close_all_fds();
            return (0);
        }  
        if (ft_strcmp(line, cmd->heredoc_delimiter) == 0)
        {
            free(line);
			close(fd);
            break;
        }    
		if (has_expandable_dollar(line))
        {
            expanded_line = expand_variables(line, ctx);
            free(line);
            line = expanded_line;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    int read_fd = open(file_name, O_RDONLY);
    if (read_fd == -1)
    {
		unlink(file_name);
        return (0);
    }
    dup2(read_fd, STDIN_FILENO);
    close(read_fd);
    unlink(file_name);

    return (1);
}
