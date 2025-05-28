/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parce_util_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:56 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/28 09:27:06 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_arg(t_cmd *cmd, char *value)
{
	int		i;
	char	**new_args;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			new_args[i] = ft_strdup(cmd->args[i]);
			i++;
		}
		free_split(cmd->args);
	}
	new_args[i++] = ft_strdup(value);
	new_args[i] = NULL;
	cmd->args = new_args;
}

void	add_redir(t_redir **redir_list, char *filename, int type)
{
	t_redir	*new_node;
	t_redir	*tmp;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return ;
	if (type == HEREDOC)
		new_node->file = get_here_doc(filename);
	else
		new_node->file = ft_strdup(filename);
	new_node->type = type;
	new_node->next = NULL;
	if (*redir_list == NULL)
		*redir_list = new_node;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	print_redirs(t_redir *redir)
{
	const char	*type_str = NULL;

	while (redir)
	{
		if (redir->type == REDIRECTION_IN)
			type_str = "<";
		else if (redir->type == HEREDOC)
			type_str = "<<";
		else if (redir->type == REDIRECTION_OUT)
			type_str = ">";
		else if (redir->type == APPEND)
			type_str = ">>";
		else
			type_str = "?";
		printf("  %s %s\n", type_str, redir->file);
		redir = redir->next;
	}
}
