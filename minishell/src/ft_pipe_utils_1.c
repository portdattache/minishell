/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:24:03 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/24 15:02:51 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	manag_outfile(t_cmd *cmd, int *pipe_fd)
{
	int	out_fd;

	if (cmd->outfile == NULL && cmd->next == NULL)
		return (0);
	if (cmd->outfile == NULL)
	{
		if (pipe_fd[1] >= 0)
			dup2(pipe_fd[1], 1);
		return (0);
	}
	out_fd = last_outfile(cmd);
	if (out_fd == -1)
	{
		if (pipe_fd[1] >= 0)
			dup2(pipe_fd[1], 1);
		return (-1);
	}
	dup2(out_fd, 1);
	close(out_fd);
	return (0);
}
