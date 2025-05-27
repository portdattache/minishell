/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:22:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/27 09:20:22 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_data *data, t_cmd *cmd, int stdin, int stdout)
{
	reset_signals_child();
	signal(SIGPIPE, SIG_IGN);
	dprintf(1, "je passe dans l'enfant\n");
	if (redirect_management(cmd) == -1)
		ft_exit_exec(1, data, cmd);
	if (is_builtin(cmd->args[0]))
		ft_exit_exec(run_builtin(data, cmd, stdin, stdout), data, cmd);
	g_status = handle_exec(data, cmd);
	ft_exit_exec(127, data, cmd);
}

int	ft_process(t_data *data, t_cmd *cmd, int stdin, int stdout)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	ret = prepare_cmd_path(data, cmd);
	if (ret != 0)
		return (ret);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (CODE_FAIL);
	}
	if (pid == 0)
		exec_child(data, cmd, stdin, stdout);
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

int	handle_exec(t_data *data, t_cmd *cmd)
{
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		if (access(cmd->args[0], F_OK) == -1)
			no_such_file_or_directory(cmd->args[0]);
		else if (access(cmd->args[0], X_OK) == -1)
			permission_denied(cmd->args[0]);
		else
			execve(cmd->args[0], cmd->args, data->envp);
		return (126);
	}
	if (cmd->path)
	{
		if (access(cmd->path, X_OK) == -1)
			permission_denied(cmd->path);
		else
			execve(cmd->path, cmd->args, data->envp);
		error_message(cmd->args[0]);
		return (126);
	}
	error_message(cmd->args[0]);
	return (127);
}

int	prepare_cmd_path(t_data *data, t_cmd *cmd)
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
