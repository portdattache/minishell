/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:51:18 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/01 23:51:53 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

int	run_builtin(t_data *data, t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(data));
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(data, cmd));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(data));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(data, cmd, STDIN_FILENO, STDOUT_FILENO));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(data));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(data));
	return (1);
}
