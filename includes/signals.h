/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:55:20 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/10 22:15:20 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include <signal.h>

extern volatile sig_atomic_t g_signal_received;

// Funções de configuração de signals
void	setup_signals(void);
void	setup_signals_child(void);
void	setup_signals_ignore(void);
void	restore_signals(void);

// Handlers
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

void setup_signals_heredoc(void);
void setup_signals_heredoc(void);

#endif