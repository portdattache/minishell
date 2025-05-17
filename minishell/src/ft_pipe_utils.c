/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:53:52 by broboeuf          #+#    #+#             */
/*   Updated: 2025/05/17 16:53:54 by broboeuf         ###   ########.fr       */
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
			error_message(str); /* perror(str) ou équivalent */
	}
	return (fd);
}

int	last_infile(t_cmd *cmd)
{
	int		fd;
	int		prev_file_fd;
	t_redir	*infile;

	prev_file_fd = -1;
	infile = cmd->infile;
	fd = -1;
	while (infile)
	{
		if (prev_file_fd != -1)
			safe_close(prev_file_fd);
		fd = open_infile(infile->file);
		if (fd == -1)
			return (-1);
		prev_file_fd = fd;
		infile = infile->next;
	}
	return (fd);
}

int	manag_infile(t_cmd *cmd, int prev_fd_pipe_read)
{
	int	in_file_fd;

	if (cmd->infile == NULL)
	{
		if (prev_fd_pipe_read >= 0)
		{
			if (dup2(prev_fd_pipe_read, STDIN_FILENO) < 0)
			{
				error_message("dup2 manag_infile pipe");
				safe_close(prev_fd_pipe_read);
				return (CODE_FAIL);
			}
			safe_close(prev_fd_pipe_read);
		}
		return (CODE_SUCCESS);
	}
	if (prev_fd_pipe_read >= 0)
		safe_close(prev_fd_pipe_read);
	in_file_fd = last_infile(cmd);
	if (in_file_fd == -1)
		return (CODE_FAIL);
	if (dup2(in_file_fd, STDIN_FILENO) < 0)
	{
		error_message("dup2 manag_infile file");
		safe_close(in_file_fd);
		return (CODE_FAIL);
	}
	safe_close(in_file_fd);
	return (CODE_SUCCESS);
}

int	open_outfile(char *file, t_TokenType mode)
{
	int	fd;

	if (mode == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else /* REDIRECTION_OUT */
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		/* Logique d'erreur originale (ou similaire à celle-ci) */
		if (access(file, F_OK) == -1) /* Vérifie si le fichier n'existe pas */
			no_such_file_or_directory(file);
		/* Si le fichier existe mais on ne peut pas écrire (ex: permissions) */
		/* ou si c'est un répertoire (open échouera avec EISDIR) */
		/* ou autre erreur d'ouverture. */
		else if (access(file, W_OK) == -1)
			/* Vérifie les permissions d'écriture si F_OK est vrai */
			permission_denied(file);
		else
			error_message(file); /* Cas générique, pourrait être is_a_directory,
				etc. */
	}
	return (fd);
}

int	last_outfile(t_cmd *cmd)
{
	int		fd;
	int		prev_file_fd;
	t_redir	*outfile;

	prev_file_fd = -1;
	outfile = cmd->outfile;
	fd = -1;
	while (outfile)
	{
		if (prev_file_fd != -1)
			safe_close(prev_file_fd);
		fd = open_outfile(outfile->file, (t_TokenType)outfile->type);
		if (fd == -1)
			return (-1);
		prev_file_fd = fd;
		outfile = outfile->next;
	}
	return (fd);
}

int	manag_outfile(t_cmd *cmd, int *current_cmd_pipe_fd)
{
	int	out_file_fd;

	if (cmd->outfile == NULL)
	{
		if (cmd->next != NULL)
		{
			if (current_cmd_pipe_fd[1] >= 0)
			{
				if (dup2(current_cmd_pipe_fd[1], STDOUT_FILENO) < 0)
				{
					error_message("dup2 manag_outfile pipe");
					safe_close(current_cmd_pipe_fd[1]);
					return (CODE_FAIL);
				}
				safe_close(current_cmd_pipe_fd[1]);
			}
		}
		return (CODE_SUCCESS);
	}
	out_file_fd = last_outfile(cmd);
	if (out_file_fd == -1)
		return (CODE_FAIL);
	if (dup2(out_file_fd, STDOUT_FILENO) < 0)
	{
		error_message("dup2 manag_outfile file");
		safe_close(out_file_fd);
		return (CODE_FAIL);
	}
	safe_close(out_file_fd);
	return (CODE_SUCCESS);
}
