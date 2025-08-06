#include "signal.h"
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "context_types.h"
#include "lib_ft.h"

extern volatile sig_atomic_t g_signal_received;

void handle_sigint(int sig)
{
    (void)sig;
    g_signal_received = sig;
    ft_putchar_fd('\n', STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigquit(int sig)
{
    (void)sig;
    // ctrl-\ não faz nada
}

void setup_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
//nos processos filhos
void setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);  // ctrl-C
	signal(SIGQUIT, SIG_DFL); // ctrl-
}
//para ignorar durante pipes ou execução de comandos
void setup_signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);  // ctrl-C
	signal(SIGQUIT, SIG_IGN); // ctrl-
}
void restore_signals(void)
{
	setup_signals();  
}

