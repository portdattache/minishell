/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:37:08 by garside           #+#    #+#             */
/*   Updated: 2025/06/04 22:42:42 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_for_children(pid_t last_pid, t_data *data)
{
	int		status;
	pid_t	wpid;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFSIGNALED(status))
				data->last_status = 128 + WTERMSIG(status);
			else
				data->last_status = WEXITSTATUS(status);
		}
		wpid = wait(&status);
	}
	return (data->last_status);
}

char	*get_cmd_path(t_data *data, char **cmd)
{
	return (find_cmd_path(cmd[0], data));
}

void	maybe_close(t_cmd *cmd, int *prev_fd)
{
	safe_close(cmd->pipe_fd[PIPE_WRITE]);
	*prev_fd = cmd->pipe_fd[PIPE_READ];
}
