/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:45:06 by garside           #+#    #+#             */
/*   Updated: 2025/05/17 16:49:01 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal(void)
{
	signal(SIGINT, handle_sigint); // Ctrl+C annule la ligne en shell
	signal(SIGQUIT, SIG_IGN);      // Ctrl+\ ignoré en shell
}

void	reset_signals_child(void)
{
	signal(SIGINT, SIG_DFL);  // Ctrl+C interrompt la commande
	signal(SIGQUIT, SIG_DFL); // Ctrl+\ interrompt la commande
}
