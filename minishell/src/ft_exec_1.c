/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:13:30 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/27 15:26:32 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_for_pipeline(pid_t last_pid, t_data *data)
{
	int		status;
	pid_t	wpid;

	(void)data;
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid)
			g_status = WEXITSTATUS(status);
		wpid = wait(&status);
	}
}

int	exec_line(t_data *data, t_cmd *cmd)
{
	pid_t	last_pid;

	if (!cmd->next)
		return (handle_single_command(data, cmd));
	last_pid = handle_pipeline(data, cmd);
	if (last_pid == -1)
		return (CODE_FAIL);
	wait_for_pipeline(last_pid, data);
	if (cmd)
		free_cmd_list(data);
	return (g_status);
}

int	init_pipe_if_needed(t_cmd *cmd)
{
	if (cmd->next && pipe(cmd->pipe_fd) == -1)
	{
		perror("pipe error");
		return (-1);
	}
	if (!cmd->next)
	{
		cmd->pipe_fd[0] = -1;
		cmd->pipe_fd[1] = -1;
	}
	return (0);
}

void	update_fds_after_process(t_cmd *cmd, t_exec_fd *fds)
{
	if (fds->prev_fd != -1)
		safe_close(fds->prev_fd);
	if (cmd->next)
	{
		safe_close(cmd->pipe_fd[1]);
		fds->prev_fd = cmd->pipe_fd[0];
	}
	else
		fds->prev_fd = -1;
}

pid_t	handle_pipeline(t_data *data, t_cmd *cmd)
{
	t_exec_fd	fds;
	pid_t		last_pid;

	fds.prev_fd = -1;
	last_pid = -1;
	while (cmd)
	{
		if (init_pipe_if_needed(cmd) == -1)
			return (-1);
		last_pid = ft_process(data, cmd, &fds);
		update_fds_after_process(cmd, &fds);
		cmd = cmd->next;
	}
	if (fds.prev_fd != -1)
		safe_close(fds.prev_fd);
	return (last_pid);
}
