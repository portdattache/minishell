/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:01:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 08:03:51 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt(t_shell *shell)
{
	while (1)
	{
		shell->input_terminal = readline("\033[31mminishell> \033[0m");
		if (!shell->input_terminal)
		{
			printf("exit\n");
			exit(0);
		}
		if (*shell->input_terminal)
			add_history(shell->input_terminal);
		printf("Commande entree: %s\n", shell->input_terminal);
		if (strcmp("exit", shell->input_terminal) == 0)
		{
			free(shell->input_terminal);
			exit(1);
		}
		free(shell->input_terminal);
	}
}
