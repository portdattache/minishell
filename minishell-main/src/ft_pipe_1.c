/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:22:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/23 12:23:20 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_data *data, t_cmd *cmd, int prev_fd, int stdin, int stdout)
{
	reset_signals_child();
	signal(SIGPIPE, SIG_IGN);
	if (redirect_management(cmd, prev_fd) == -1)
		ft_exit_exec(1, data, cmd);
	if (is_builtin(cmd->args[0]))
		ft_exit_exec(run_builtin(data, cmd, stdin, stdout), data, cmd);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		if (access(cmd->args[0], F_OK) == -1)
			no_such_file_or_directory(cmd->args[0]);
		else if (access(cmd->args[0], X_OK) == -1)
			permission_denied(cmd->args[0]);
		else
			execve(cmd->args[0], cmd->args, data->envp);
		ft_exit_exec(126, data, cmd);
	}
	if (cmd->path)
	{
		if (access(cmd->path, X_OK) == -1)
			permission_denied(cmd->path);
		else
			execve(cmd->path, cmd->args, data->envp);
		error_message(cmd->args[0]);
		ft_exit_exec(126, data, cmd);
	}
	error_message(cmd->args[0]);
	ft_exit_exec(127, data, cmd);
}

int	ft_process(t_data *data, t_cmd *cmd, int prev_fd, int stdin, int stdout)
{
	pid_t	pid;

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
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (CODE_FAIL);
	}
	if (pid == 0)
		exec_child(data, cmd, prev_fd, stdin, stdout);
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	return (pid);
}

int	ft_charnull(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}
