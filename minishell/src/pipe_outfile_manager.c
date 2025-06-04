/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_outfile_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:49:28 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/03 17:22:25 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_outfile(char *file, t_TokenType mode)
{
	int	fd;

	if (mode == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (access(file, F_OK) == -1)
			no_such_file_or_directory(file);
		else if (access(file, W_OK) == -1)
			permission_denied(file);
		else
			error_message(file);
	}
	return (fd);
}

int	last_outfile(t_cmd *cmd)
{
	int		fd;
	int		prev_fd;
	t_redir	*outfile;

	outfile = cmd->outfile;
	prev_fd = -1;
	while (outfile)
	{
		fd = open_outfile(outfile->file, outfile->type);
		if (fd == -1)
		{
			if (prev_fd != -1)
				safe_close(prev_fd);
			return (-1);
		}
		if (prev_fd != -1)
			safe_close(prev_fd);
		prev_fd = fd;
		outfile = outfile->next;
	}
	return (fd);
}

int	manag_outfile(t_cmd *cmd, int *pipe_fd)
{
	int	out_fd;

	if (cmd->outfile == NULL && cmd->next == NULL)
		return (0);
	if (cmd->outfile == NULL)
	{
		if (pipe_fd[PIPE_WRITE] >= 0)
		{
			dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
			safe_close(pipe_fd[PIPE_WRITE]);
			safe_close(pipe_fd[PIPE_READ]);
		}
		return (0);
	}
	out_fd = last_outfile(cmd);
	if (out_fd == -1)
	{
		if (pipe_fd[PIPE_WRITE] >= 0)
			dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
		return (1);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	return (0);
}
