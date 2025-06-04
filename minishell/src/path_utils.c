/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:32:19 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/04 10:33:05 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	resolve_command_path(t_data *data, t_cmd *cmd)
{
	if (cmd->args && cmd->args[0] && !is_builtin(cmd->args[0])
		&& cmd->args[0][0] != '.' && cmd->args[0][0] != '/')
	{
		cmd->path = find_cmd_path(cmd->args[0], data);
		if (!cmd->path)
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			return (127);
		}
	}
	return (0);
}

void	is_not_path(t_data *data)
{
	ft_putstr_fd(data->token->value, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (data->cmd_list)
		free_cmd_list(data);
	free_data(data);
	exit(127);
}
