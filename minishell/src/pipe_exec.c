/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:27:48 by garside           #+#    #+#             */
/*   Updated: 2025/06/04 22:34:24 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_process(t_data *data, t_cmd *cmd, int prev_fd)
{
	pid_t	pid;
	int		ret;

	ret = resolve_command_path(data, cmd);
	if (ret != 0)
		return (ret);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (CODE_FAIL);
	}
	if (pid == 0)
		exec_child(data, cmd, prev_fd);
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	return (pid);
}

void	exec_child(t_data *data, t_cmd *cmd, int prev_fd)
{
	reset_signals_child();
	if (!cmd || !cmd->args || !cmd->args[0])
		handle_invalid_command(data, cmd, prev_fd);
	if (redirect_management(cmd, prev_fd) == 1)
		ft_exit_exec(1, data, cmd);
	if (is_builtin(cmd->args[0]))
		ft_exit_exec(run_builtin(data, cmd), data, cmd);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
		handle_direct_exec(data, cmd);
	if (cmd->path)
		handle_path_exec(data, cmd);
	error_message(cmd->args[0]);
	ft_exit_exec(127, data, cmd);
}
