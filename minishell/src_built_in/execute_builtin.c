/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:55:23 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/22 14:43:43 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(char **args, t_shell *shell)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args, shell));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args, shell));
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, shell));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, shell));
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(shell));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	return (1);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	return (0);
}
