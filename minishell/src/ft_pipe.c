/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:27:48 by garside           #+#    #+#             */
/*   Updated: 2025/05/27 14:12:08 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit_exec(int code, t_data *data, t_cmd *cmd)
{
	if (cmd && cmd->path)
		free(cmd->path);
	if (data)
	{
		free_cmd_list(data);
		free_data(data);
	}
	exit(code);
}

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

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

int	redirect_management(t_cmd *cmd, t_exec_fd *fds)
{
	if (manag_infile(cmd) == 1)
	{
		safe_close(cmd->pipe_fd[0]);
		safe_close(cmd->pipe_fd[1]);
		return (1);
	}
	if (manag_outfile(cmd, cmd->pipe_fd) == 1)
	{
		safe_close(cmd->pipe_fd[0]);
		safe_close(cmd->pipe_fd[1]);
		return (1);
	}
	safe_close(cmd->pipe_fd[0]);
	safe_close(cmd->pipe_fd[1]);
	return (0);
}

int	run_builtin(t_data *data, t_cmd *cmd, int stdin, int stdout)
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
		return (ft_exit(data, cmd, stdin, stdout));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(data));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(data));
	else if (ft_strcmp(cmd->args[0], ":") == 0)
		return (ft_charnull(cmd));
	return (1);
}
