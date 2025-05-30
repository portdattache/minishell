/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_manage_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:28:30 by garside           #+#    #+#             */
/*   Updated: 2025/05/30 17:01:55 by bcaumont         ###   ########.fr       */
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

int	manag_infile(t_cmd *cmd, t_exec_fd *fds)
{
	int	in_fd;

	if (cmd->infile == NULL && fds->prev_fd == 0)
		return (0);
	if (cmd->infile == NULL && fds->prev_fd != 0)
		return (dup2(fds->prev_fd, PIPE_READ), safe_close(fds->prev_fd), 0);
	if (fds->prev_fd != 0)
		safe_close(fds->prev_fd);
	in_fd = last_infile(cmd);
	if (in_fd == -1)
		return (1);
	return (dup2(in_fd, PIPE_READ), safe_close(in_fd), 0);
}
