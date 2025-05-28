/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:27:12 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/27 19:27:27 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_child_process(t_data *data, t_exec_fd *fds)
{
	char	**cmd;
	char	*path;

	cmd = ft_get_cmd(data);
	path = get_cmd_path(data, cmd);
	close(fds->saved_stdin);
	close(fds->saved_stdout);
	if (!path)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(data->token->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_cmd_list(data);
		free_data(data);
		free_split(cmd);
		exit(127);
	}
	execve(path, cmd, data->envp);
	ft_putstr_fd("execve failed\n", 2);
	free_cmd_list(data);
	free_data(data);
	free_split(cmd);
	free(path);
	exit(127);
}
