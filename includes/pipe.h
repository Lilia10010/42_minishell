
#ifndef PIPE_H
# define PIPE_H

typedef struct s_context	t_context;
typedef struct s_command	t_command;

int	execute_pipe(t_command *commands, t_context *ctx);
int	process_single_command(t_command *current, t_context *ctx,
								int *prev_fd, int *last_pid);
int	handle_pipe_creation(int pipe_fd[2], t_command *current);
void	cleanup_parent_fds(int prev_fd, t_command *current, int pipe_fd[2]);
void	setup_child_input(int prev_fd);
void	setup_child_output(t_command *current, int pipe_fd[2]);

#endif