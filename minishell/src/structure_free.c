/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:00:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/04 22:34:34 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->type == HEREDOC && redir->file)
			unlink(redir->file);
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_env_list(data->env);
	free_env_list(data->export);
	free(data->input);
	free_token(data->token);
}

void	free_name_content(char *name, char *content)
{
	free(name);
	if (content)
		free(content);
}
