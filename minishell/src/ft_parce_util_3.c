/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parce_util_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:41:50 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/24 15:42:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmds(t_cmd *cmd)
{
	while (cmd)
	{
		printf("---- Commande ----\n");
		print_cmd_args(cmd->args);
		print_cmd_redirs(cmd);
		cmd = cmd->next;
	}
}

void	print_cmd_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		printf("Args : ");
		while (args[i])
			printf("[%s] ", args[i++]);
		printf("\n");
	}
	else
		printf("Args : (aucun)\n");
}

void	print_cmd_redirs(t_cmd *cmd)
{
	printf("Redirs in  :\n");
	if (cmd->infile)
		print_redirs(cmd->infile);
	else
		printf("  (aucune)\n");
	printf("Redirs out :\n");
	if (cmd->outfile)
		print_redirs(cmd->outfile);
	else
		printf("  (aucune)\n");
}
