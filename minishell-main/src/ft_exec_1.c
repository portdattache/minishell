/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:13:30 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/23 12:14:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_pipeline(pid_t last_pid, t_data *data)
{
	int		status;
	pid_t	wpid;

	while ((wpid = wait(&status)) > 0)
	{
		if (wpid == last_pid)
			data->last_status = WEXITSTATUS(status);
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
	return (data->last_status);
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

void	update_fds_after_process(t_cmd *cmd, int *prev_fd)
{
	if (*prev_fd != -1)
		safe_close(*prev_fd);
	if (cmd->next)
	{
		safe_close(cmd->pipe_fd[1]);
		*prev_fd = cmd->pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

pid_t	handle_pipeline(t_data *data, t_cmd *cmd)
{
	int		prev_fd;
	pid_t	last_pid;

	prev_fd = -1;
	last_pid = -1;
	while (cmd)
	{
		if (init_pipe_if_needed(cmd) == -1)
			return (-1);
		last_pid = ft_process(data, cmd, prev_fd, STDIN_FILENO, STDOUT_FILENO);
		update_fds_after_process(cmd, &prev_fd);
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		safe_close(prev_fd);
	return (last_pid);
}
