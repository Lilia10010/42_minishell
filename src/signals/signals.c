/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:10:10 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 21:58:57 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "lib_ft.h"
#include "signals.h"

volatile sig_atomic_t	g_signal_received = 0;

// void	handle_sigint_heredoc(int sig)
// {
// 	g_signal_received = sig;
// 	rl_done = 1;
// 	write(STDOUT_FILENO, "\n", 1);
// }

// void	setup_signals_heredoc(void)
// {
// 	signal(SIGINT, handle_sigint_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGTSTP, SIG_IGN);
// }

void	handle_sigint(int sig)
{
	g_signal_received = sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// void	handle_sigquit(int sig)
// {
// 	(void)sig;
// }

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	setup_signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	setup_signals();
}
