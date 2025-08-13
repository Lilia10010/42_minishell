/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:55:20 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/13 18:30:45 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal_received;

void	setup_signals(void);
void	setup_signals_child(void);
void	setup_signals_ignore(void);
void	restore_signals(void);

void	handle_sigint(int sig);
void	handle_sigquit(int sig);

void	setup_signals_heredoc(void);
void	setup_signals_heredoc(void);

#endif
