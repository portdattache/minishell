/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:28:30 by garside           #+#    #+#             */
/*   Updated: 2025/05/27 12:59:58 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_infile(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		if (access(str, F_OK) == -1)
			no_such_file_or_directory(str);
		else if (access(str, R_OK) == -1)
			permission_denied(str);
		else
			error_message(str);
	}
	return (fd);
}

int	last_infile(t_cmd *cmd)
{
	int		fd;
	t_redir	*infile;

	cmd->prev_fd = -1;
	infile = cmd->infile;
	while (infile)
	{
		fd = open_infile(infile->file);
		if (fd == -1)
		{
			if (cmd->prev_fd != -1)
				safe_close(cmd->prev_fd);
			return (-1);
		}
		if (cmd->prev_fd != -1)
			safe_close(cmd->prev_fd);
		cmd->prev_fd = fd;
		infile = infile->next;
	}
	return (fd);
}

int	manag_infile(t_cmd *cmd)
{
	int	in_fd;

	if (cmd->infile == NULL && cmd->prev_fd == 0)
		return (0);
	if (cmd->infile == NULL && cmd->prev_fd != 0)
		return (dup2(cmd->prev_fd, PIPE_READ), safe_close(cmd->prev_fd), 0);
	if (cmd->prev_fd != 0)
		safe_close(cmd->prev_fd);
	in_fd = last_infile(cmd);
	if (in_fd == -1)
		return (1);
	return (dup2(in_fd, PIPE_READ), safe_close(in_fd), 0);
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
