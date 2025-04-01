/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:01:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/01 09:50:36 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt(t_shell *shell)
{
	char	*line;
	char	**args;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (*line)
			add_history(shell->history);
		printf("Commande entree: %s\n", line);
		if (strcmp("exit", shell->input) == 0)
		{
			free(shell->input);
			exit(1);
		}
		free(shell->input);
	}
}
