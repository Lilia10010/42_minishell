
#include "minishell.h"

/* Função para aplicar redirecionamento de entrada */
static int apply_input_redirection(t_command *cmd)
{
    int fd;

    if (!cmd->input_file)
        return (1);

    fd = open(cmd->input_file, O_RDONLY);
    if (fd == -1)
    {
        perror(cmd->input_file);
        return (0);
    }

    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2 input");
        close(fd);
        return (0);
    }

    close(fd);
    return (1);
}

/* Função para aplicar redirecionamento de saída */
static int apply_output_redirection(t_command *cmd)
{
    int fd;
    int flags;

    if (!cmd->output_file)
        return (1);

    if (cmd->append_mode)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
        flags = O_WRONLY | O_CREAT | O_TRUNC;

    fd = open(cmd->output_file, flags, 0644);
    if (fd == -1)
    {
        perror(cmd->output_file);
        return (0);
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2 output");
        close(fd);
        return (0);
    }

    close(fd);
    return (1);
}

/* Função para lidar com heredoc */
static int apply_heredoc_redirection(t_command *cmd)
{
    int pipefd[2];
    char *line;

    if (!cmd->heredoc_mode || !cmd->heredoc_delimiter)
        return (1);

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (0);
    }

    printf("heredoc> ");
    while ((line = get_next_line(STDIN_FILENO)) != NULL)
    {
        // Remove o \n do final se existir
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';

        if (ft_strcmp(line, cmd->heredoc_delimiter) == 0)
        {
            free(line);
            break;
        }

        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
        printf("heredoc> ");
    }

    close(pipefd[1]);

    if (dup2(pipefd[0], STDIN_FILENO) == -1)
    {
        perror("dup2 heredoc");
        close(pipefd[0]);
        return (0);
    }

    close(pipefd[0]);
    return (1);
}

/* Função principal para aplicar todos os redirecionamentos */
int apply_redirections(t_command *cmd)
{
    if (!cmd)
        return (1);

    // Aplica redirecionamento de entrada (< ou <<)
    if (cmd->heredoc_mode)
    {
        if (!apply_heredoc_redirection(cmd))
            return (0);
    }
    else if (cmd->input_file)
    {
        if (!apply_input_redirection(cmd))
            return (0);
    }

    // Aplica redirecionamento de saída (> ou >>)
    if (cmd->output_file)
    {
        if (!apply_output_redirection(cmd))
            return (0);
    }

    return (1);
}

/* Função para salvar os file descriptors originais */
void save_original_fds(int *original_stdin, int *original_stdout)
{
    *original_stdin = dup(STDIN_FILENO);
    *original_stdout = dup(STDOUT_FILENO);
}

/* Função para restaurar os file descriptors originais */
void restore_original_fds(int original_stdin, int original_stdout)
{
    if (original_stdin != -1)
    {
        dup2(original_stdin, STDIN_FILENO);
        close(original_stdin);
    }
    if (original_stdout != -1)
    {
        dup2(original_stdout, STDOUT_FILENO);
        close(original_stdout);
    }
}

/* Versão atualizada do execute_single_command com redirecionamentos */
int execute_single_command(t_command *cmd, t_context *ctx)
{
    int original_stdin, original_stdout;
    int result;

    if (!cmd || !cmd->args || !cmd->args[0])
    {
        ctx->exit_status = 0;
        return (0);
    }

    // Salva os file descriptors originais
    save_original_fds(&original_stdin, &original_stdout);

    // Aplica redirecionamentos
    if (!apply_redirections(cmd))
    {
        restore_original_fds(original_stdin, original_stdout);
        ctx->exit_status = 1;
        return (1);
    }

    // Executa o comando
    if (get_builtin_id(cmd->args[0]) != BUILTIN_NONE)
        result = builtin_dispatcher(cmd, ctx);
    else if (is_path_command(cmd->args[0]))
        result = execute_path_command(cmd, ctx);
    else
        result = execute_command_from_path(cmd, ctx);

    // Restaura os file descriptors originais
    restore_original_fds(original_stdin, original_stdout);

    return (result);
}

/* Exemplo de implementação para comando simples com redirecionamento */
static int execute_simple_with_redirection(t_command *cmd, t_context *ctx)
{
    pid_t pid;
    int status;
    int original_stdin, original_stdout;

    // Salva FDs originais
    save_original_fds(&original_stdin, &original_stdout);

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        restore_original_fds(original_stdin, original_stdout);
        return (1);
    }

    if (pid == 0) // Processo filho
    {
        // Aplica redirecionamentos no processo filho
        if (!apply_redirections(cmd))
            exit(1);

        // Executa o comando
        if (execvp(cmd->args[0], cmd->args) == -1)
        {
            perror(cmd->args[0]);
            exit(127);
        }
    }
    else // Processo pai
    {
        waitpid(pid, &status, 0);
        restore_original_fds(original_stdin, original_stdout);
        
        if (WIFEXITED(status))
            ctx->exit_status = WEXITSTATUS(status);
        else
            ctx->exit_status = 1;
    }

    return (ctx->exit_status);
}

/* Função auxiliar para verificar se é um token de redirecionamento */
int is_redirection_token(int token_type)
{
    return (token_type == TOKEN_REDIRECT_IN ||
            token_type == TOKEN_REDIRECT_OUT ||
            token_type == TOKEN_REDIRECT_OUT_APPEND ||
            token_type == TOKEN_HEREDOC);
}

/* Função para validar se o arquivo pode ser criado/aberto */
int validate_redirection_file(char *filename, int is_output)
{
    int fd;

    if (!filename)
        return (0);

    if (is_output)
    {
        // Tenta criar/abrir o arquivo para escrita
        fd = open(filename, O_WRONLY | O_CREAT, 0644);
        if (fd == -1)
        {
            perror(filename);
            return (0);
        }
        close(fd);
    }
    else
    {
        // Verifica se o arquivo existe e pode ser lido
        fd = open(filename, O_RDONLY);
        if (fd == -1)
        {
            perror(filename);
            return (0);
        }
        close(fd);
    }

    return (1);
}

/* Versão atualizada do execute_command para lidar com redirecionamentos */
int execute_command(t_command *commands, t_context *ctx)
{
    printf("entrou no xxxxxxxxxxxx\n");
    
    if (!commands)
        return (0);

    // Se é um comando único, executa com redirecionamentos
    if (!commands->next)
        return (execute_single_command(commands, ctx));

    // Se há múltiplos comandos (pipes), executa o pipeline
    return (execute_pipe(commands, ctx));
}

/* Exemplo de como o execute_pipe deve ser adaptado para redirecionamentos */
static int execute_pipe_with_redirections(t_command *commands, t_context *ctx)
{
    int pipefd[2];
    pid_t pid1, pid2;
    int status;
    t_command *cmd1 = commands;
    t_command *cmd2 = commands->next;

    // Cria o pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (1);
    }

    // Primeiro processo
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return (1);
    }

    if (pid1 == 0) // Primeiro filho
    {
        close(pipefd[0]); // Fecha leitura do pipe
        
        // Aplica redirecionamento de entrada se houver
        if (cmd1->input_file || cmd1->heredoc_mode)
        {
            if (!apply_redirections(cmd1))
                exit(1);
        }
        
        // Redireciona stdout para o pipe (a menos que haja redirecionamento de saída)
        if (!cmd1->output_file)
        {
            if (dup2(pipefd[1], STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(1);
            }
        }
        else
        {
            // Se há redirecionamento de saída, aplica ele
            if (!apply_output_redirection(cmd1))
                exit(1);
        }
        
        close(pipefd[1]);
        
        if (execvp(cmd1->args[0], cmd1->args) == -1)
        {
            perror(cmd1->args[0]);
            exit(127);
        }
    }

    // Segundo processo
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return (1);
    }

    if (pid2 == 0) // Segundo filho
    {
        close(pipefd[1]); // Fecha escrita do pipe
        
        // Redireciona stdin para o pipe (a menos que haja redirecionamento de entrada)
        if (!cmd2->input_file && !cmd2->heredoc_mode)
        {
            if (dup2(pipefd[0], STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(1);
            }
        }
        else
        {
            // Se há redirecionamento de entrada, aplica ele
            if (!apply_redirections(cmd2))
                exit(1);
        }
        
        // Aplica redirecionamento de saída se houver
        if (cmd2->output_file)
        {
            if (!apply_output_redirection(cmd2))
                exit(1);
        }
        
        close(pipefd[0]);
        
        if (execvp(cmd2->args[0], cmd2->args) == -1)
        {
            perror(cmd2->args[0]);
            exit(127);
        }
    }

    // Processo pai
    close(pipefd[0]);
    close(pipefd[1]);
    
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    
    if (WIFEXITED(status))
        ctx->exit_status = WEXITSTATUS(status);
    else
        ctx->exit_status = 1;

    return (ctx->exit_status);
}


static int	check_digit(char *arg)
{
	if (!arg || !*arg)
		return (0);
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	builtin_exit(char **args, t_context *ctx)
{
	int	exit_code = 0;

	if (!args[1])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(ctx->exit_status);
	}

	if (args[2])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("Minishell: exit: too many arguments\n", STDERR_FILENO);
		ctx->exit_status = 1;
		return (1);
	}

	if (!check_digit(args[1]))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2); // mesmo comportamento que seu exemplo funcional
	}

	exit_code = ft_atoi(args[1]) % 256;
	ctx->exit_status = exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}
