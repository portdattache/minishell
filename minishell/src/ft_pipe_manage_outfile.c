/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_manage_file_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:24:03 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/30 17:01:59 by bcaumont         ###   ########.fr       */
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
