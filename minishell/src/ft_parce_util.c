/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parce_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:47:16 by garside           #+#    #+#             */
/*   Updated: 2025/05/24 12:13:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd_list(t_data *data)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!data || !data->cmd_list)
		return ;
	current = data->cmd_list;
	while (current)
	{
		next = current->next;
		if (current->outfile)
			free_redir_list(current->outfile);
		if (current->infile)
			free_redir_list(current->infile);
		if (current->args)
			free_split(current->args);
		free(current);
		current = next;
	}
	data->cmd_list = NULL;
}

t_cmd	*new_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	cmd->prev_fd = -1;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	return (cmd);
}
