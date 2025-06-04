/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:40:43 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/04 10:41:21 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_management(t_cmd *cmd, int prev_fd)
{
	if (manag_infile(cmd, prev_fd) == 1)
	{
		safe_close(cmd->pipe_fd[PIPE_READ]);
		safe_close(cmd->pipe_fd[PIPE_WRITE]);
		return (1);
	}
	if (manag_outfile(cmd, cmd->pipe_fd) == 1)
	{
		safe_close(cmd->pipe_fd[PIPE_READ]);
		safe_close(cmd->pipe_fd[PIPE_WRITE]);
		return (1);
	}
	safe_close(cmd->pipe_fd[PIPE_READ]);
	safe_close(cmd->pipe_fd[PIPE_WRITE]);
	return (0);
}
