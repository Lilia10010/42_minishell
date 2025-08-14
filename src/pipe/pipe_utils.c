

#include <stdio.h>
#include <unistd.h>
#include "command_types.h"
#include "pipe.h"

int	handle_pipe_creation(int pipe_fd[2], t_command *current)
{
	if (current->next && pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (1);
	}
	return (0);
}

void	setup_child_input(int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

void	setup_child_output(t_command *current, int pipe_fd[2])
{
	if (current->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	cleanup_parent_fds(int prev_fd, t_command *current, int pipe_fd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (current->next)
		close(pipe_fd[1]);
}
